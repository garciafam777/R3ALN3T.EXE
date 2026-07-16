// BattleLoopAutomationTests.cpp
// Track 2: integrates the core battle loops (chip resolution, NetP randomization, grid
// placement) into the AutomationTestToolset suite. World-free + deterministic so it runs
// headlessly via the editor MCP AutomationTestToolset. Compiled only in dev automation
// builds (editor target), matching WITH_DEV_AUTOMATION_TESTS.
#if WITH_DEV_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Kismet/GameplayStatics.h"                      // SaveGameToSlot / LoadGameFromSlot / DeleteGameInSlot
#include "Engine/GameInstance.h"                       // UGameInstance (valid Outer for GameInstanceSubsystem)
#include "../Gameplay/Battle/Cards/ChipDatabase.h"   // UChipDatabase (PopulateSliceChips, ResolveChipDamage)
#include "../Gameplay/NetP/NetPRandomizer.h"         // UNetPRandomizer::RandomizeNetP (ZETA-capped)
#include "../Gameplay/Battle/Grid/BattleGridManager.h" // ABattleGridManager::TryPlaceNetPAtCell (ZETA tier clamp)
#include "../Core/Types/TrinityMatrixTypes.h"        // EGreekTier, FR3ALN3TNetPStatus
#include "../Core/Types/CombatTypes.h"               // EBattleElementType
#include "../Core/Managers/R3ALSaveGame.h"           // UR3ALSaveGame, FR3ALN3TRewardRecord (P1A3)
#include "../Services/BackendClient.h"               // ABackendClient (Area-2 mock test)

// Canonical ZETA power ceiling (mirrors PlayChipPowerCeiling in R3ALN3T_BattleManager.cpp).
// Kept here so the suite asserts the balance envelope without reaching into file-static state.
static constexpr float KPlayChipPowerCeiling = 120.f;

// --- Test 1: Chip resolution respects the ZETA power ceiling (Track 1 regression) ---
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FR3ALN3TBattleLoopChipCeiling,
    "R3ALN3T.BattleLoop.ChipDamageWithinZetaCeiling",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FR3ALN3TBattleLoopChipCeiling::RunTest(const FString& Parameters)
{
    UGameInstance* GI = NewObject<UGameInstance>();
    UChipDatabase* DB = NewObject<UChipDatabase>(GI);
    TestNotNull(TEXT("ChipDatabase constructed"), DB);
    DB->PopulateSliceChips();

    const TArray<FName> Codes = DB->GetSliceStarterFolder();
    TestTrue(TEXT("Slice folder populated (>=8 chips)"), Codes.Num() >= 8);

    int32 ResolvedCount = 0;
    for (const FName& Code : Codes)
    {
        for (int32 E = 0; E <= static_cast<int32>(EBattleElementType::Void); ++E)
        {
            const float Dmg = DB->ResolveChipDamage(Code, static_cast<EBattleElementType>(E));
            TestTrue(TEXT("Damage is finite"), FMath::IsFinite(Dmg));
            TestTrue(TEXT("Damage never exceeds ZETA power ceiling (120)"),
                     Dmg <= KPlayChipPowerCeiling + KINDA_SMALL_NUMBER);
            ++ResolvedCount;
        }
    }
    TestTrue(TEXT("Resolved every chip x element combo"), ResolvedCount > 0);
    return true;
}

// --- Test 2: NetPRandomizer never produces OMEGA or any tier above ZETA (8000 rolls) ---
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FR3ALN3TBattleLoopRandomizerZetaCap,
    "R3ALN3T.BattleLoop.RandomizerTierCappedAtZeta",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FR3ALN3TBattleLoopRandomizerZetaCap::RunTest(const FString& Parameters)
{
    constexpr int32 Rolls = 8000;
    int32 OverZeta = 0;
    int32 OutOfElementRange = 0;
    for (int32 i = 0; i < Rolls; ++i)
    {
        const FR3ALN3TNetPStatus NetP = UNetPRandomizer::RandomizeNetP();
        if (static_cast<int32>(NetP.Tier) > static_cast<int32>(EGreekTier::Zeta))
        {
            ++OverZeta;
        }
        const int32 Elem = static_cast<int32>(NetP.Element);
        if (Elem < 1 || Elem > 21) // canon-21: Fire(1)..Void(21); None(0) excluded by design
        {
            ++OutOfElementRange;
        }
    }
    TestEqual(TEXT("Zero tiers above ZETA across 8000 rolls"), OverZeta, 0);
    TestEqual(TEXT("Zero out-of-range elements across 8000 rolls"), OutOfElementRange, 0);
    return true;
}

// --- Test 3: Grid placement clamps an OMEGA-tier NetP down to ZETA (Gate 2) ---
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FR3ALN3TBattleLoopGridTierClamp,
    "R3ALN3T.BattleLoop.GridClampsOmegaTierToZeta",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FR3ALN3TBattleLoopGridTierClamp::RunTest(const FString& Parameters)
{
    ABattleGridManager* Grid = NewObject<ABattleGridManager>();
    TestNotNull(TEXT("BattleGridManager constructed"), Grid);

    FR3ALN3TNetPStatus NetP;
    NetP.Tier = EGreekTier::Omega;          // 7 — above the ZETA ceiling
    NetP.Element = EElement::Fire;
    NetP.Construct = ENetPConstruct::Trinity;

    // col 4 satisfies the enemy-spawn gate (cols 4-7); row 0 in-bounds.
    const bool bPlaced = Grid->TryPlaceNetPAtCell(0, 4, NetP, FLinearColor::Red);
    TestTrue(TEXT("Over-ceiling NetP still placed on a valid enemy column"), bPlaced);
    TestEqual(TEXT("Tier clamped from OMEGA(7) to ZETA(1)"),
              static_cast<int32>(NetP.Tier), static_cast<int32>(EGreekTier::Zeta));
    return true;
}

// --- Test 4: Save-Game reward block round-trips across a "restart" (P1A3 Tier-3) ---
// Writes a Rotterdam FR3ALN3TRewardRecord, flushes via SaveGameToSlot, then loads
// fresh (LoadOrCreate = emulates a new session) and asserts the record survived.
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FR3ALN3TSaveGameRewardRoundTrip,
    "R3ALN3T.BattleLoop.SaveGameRewardRoundTrip",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FR3ALN3TSaveGameRewardRoundTrip::RunTest(const FString& Parameters)
{
    // Isolated slot so the test never touches the player's real save.
    const FString Slot = TEXT("R3ALN3T_TEST_RewardRT");
    const int32 UserIdx = 0;
    if (UGameplayStatics::DoesSaveGameExist(Slot, UserIdx))
    {
        UGameplayStatics::DeleteGameInSlot(Slot, UserIdx);
    }

    UGameInstance* GI = NewObject<UGameInstance>();
    UR3ALSaveGame* Save = NewObject<UR3ALSaveGame>(GI);
    TestNotNull(TEXT("SaveGame constructed"), Save);

    FR3ALN3TRewardRecord Rec;
    Rec.bPlayerWon = true;
    Rec.ZEarned = 137;
    Rec.ChipsEarned = { FName(TEXT("Buster")), FName(TEXT("ZetaBlade")) };
    Rec.XP_Earned = 42;
    Rec.EnemiesDefeated = 3;
    Rec.LocationTag = TEXT("Rotterdam");
    Rec.TimestampUTC = 1710000000;
    Save->PersistReward(Rec);

    const bool bWritten = UGameplayStatics::SaveGameToSlot(Save, Slot, UserIdx);
    TestTrue(TEXT("SaveGameToSlot succeeded"), bWritten);

    // Emulate a restart: load from disk into a NEW object.
    USaveGame* Loaded = UGameplayStatics::LoadGameFromSlot(Slot, UserIdx);
    UR3ALSaveGame* Reopen = Cast<UR3ALSaveGame>(Loaded);
    TestNotNull(TEXT("Reloaded save cast to UR3ALSaveGame"), Reopen);
    TestEqual(TEXT("RewardHistory length survived restart"), Reopen->RewardHistory.Num(), 1);
    const FR3ALN3TRewardRecord& Got = Reopen->RewardHistory[0];
    TestTrue(TEXT("bPlayerWon survived"), Got.bPlayerWon == true);
    TestEqual(TEXT("ZEarned survived"), Got.ZEarned, 137);
    TestEqual(TEXT("XP_Earned survived"), Got.XP_Earned, 42);
    TestEqual(TEXT("EnemiesDefeated survived"), Got.EnemiesDefeated, 3);
    TestEqual(TEXT("LocationTag survived"), Got.LocationTag, FString(TEXT("Rotterdam")));
    TestEqual(TEXT("TimestampUTC survived"), Got.TimestampUTC, (int64)1710000000);
    TestEqual(TEXT("ChipsEarned count survived"), Got.ChipsEarned.Num(), 2);
    if (Got.ChipsEarned.Num() == 2)
    {
        TestEqual(TEXT("Chip[0] survived"), Got.ChipsEarned[0], FName(TEXT("Buster")));
        TestEqual(TEXT("Chip[1] survived"), Got.ChipsEarned[1], FName(TEXT("ZetaBlade")));
    }

    UGameplayStatics::DeleteGameInSlot(Slot, UserIdx);
    return true;
}

// --- Test 5: Area-2 mock backend data sink — local save round-trip (no live FastAPI) ---
// The mock backend (ABackendClient::HandleMockRequest) writes player state into
// UR3ALSaveGame::PlayerNotes and flushes via UR3ALSaveGame::Save. This test exercises that
// exact local-sink path world-free, proving the standalone fallback has a real persistence
// target (no null/HTTP crash when the endpoint is down).
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBackendMockSink,
    "R3ALN3T.BattleLoop.BackendMockSink",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBackendMockSink::RunTest(const FString& Parameters)
{
    const FString Slot = TEXT("R3AL_T5_Mock");
    const uint32 UserIdx = 0;
    UGameplayStatics::DeleteGameInSlot(Slot, UserIdx);

    UObject* Outer = GetTransientPackage();
    UR3ALSaveGame* Save = UR3ALSaveGame::LoadOrCreate(Outer);
    if (!TestNotNull(TEXT("SaveGame (mock sink) constructed"), Save)) return false;

    // Mirrors ABackendClient::HandleMockRequest's player_state stash.
    Save->PlayerNotes = TEXT("{\"player_state\":{\"id\":\"test_player\",\"soul\":42}}");
    UR3ALSaveGame::Save(Outer, Save);

    UR3ALSaveGame* Reopen = UR3ALSaveGame::LoadOrCreate(Outer);
    TestNotNull(TEXT("Mock sink save reopened"), Reopen);
    if (Reopen)
    {
        TestFalse(TEXT("PlayerNotes survived restart (mock data sink)"),
                  Reopen->PlayerNotes.IsEmpty());
        TestTrue(TEXT("PlayerNotes content intact"),
                 Reopen->PlayerNotes.Contains(TEXT("test_player")));
    }

    UGameplayStatics::DeleteGameInSlot(Slot, UserIdx);
    return true;
}

// --- Test 6: Area-3 — player soul band persists to save on write ---
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSoulStatePersist,
    "R3ALN3T.BattleLoop.SoulStatePersist",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FSoulStatePersist::RunTest(const FString& Parameters)
{
    const FString Slot = TEXT("R3AL_T6_Soul");
    const uint32 UserIdx = 0;
    UGameplayStatics::DeleteGameInSlot(Slot, UserIdx);

    FSoulState Soul;
    Soul.Soul = 10.f;                 // -> Radiant band
    TestEqual(TEXT("Soul band computed Radiant"), Soul.GetBand(), ESoulAuraBand::Radiant);

    Soul.WriteToSave(GetTransientPackage());   // Area-3: flush band to on-disk save

    UR3ALSaveGame* Reopen = UR3ALSaveGame::LoadOrCreate(GetTransientPackage());
    TestNotNull(TEXT("Save reopened"), Reopen);
    if (Reopen)
    {
        TestEqual(TEXT("PlayerSoulBand survived restart"),
                  Reopen->PlayerSoulBand, ESoulAuraBand::Radiant);
    }

    UGameplayStatics::DeleteGameInSlot(Slot, UserIdx);
    return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
