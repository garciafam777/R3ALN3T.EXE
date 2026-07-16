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

#endif // WITH_DEV_AUTOMATION_TESTS
