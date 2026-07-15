// R3ALN3T_BattleManager.cpp
#include "R3ALN3T_BattleManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Cards/ChipDatabase.h" // included in .cpp only, to avoid circular include with CombatTypes.h
#include "../../Core/Types/SoulState.h" // Gap C: FSoulState, ApplyDamageFork
#include "../../Core/Managers/R3ALN3TGameInstance.h" // Gap D: UR3ALN3TGameInstance (CurrentRun souls)
#include "../../Battle/NetP/FactionTypes.h"          // FConstructRosterRow, FNetPRosterUnit
#include "../NetP/NetPRandomizer.h"                 // UNetPRandomizer::RandomizeNetP (ZETA-capped)

TArray<FR3ALN3TNetPStatus> UR3ALN3T_BattleManager::GenerateConstructSpawns(
    UDataTable* RosterTable, ENetPConstruct Construct, int32 SpawnCount) const
{
    TArray<FR3ALN3TNetPStatus> OutSpawns;

    if (!RosterTable)
    {
        UE_LOG(LogTemp, Error, TEXT("[Roster] RosterTable is NULL! Bind a ConstructRoster DataTable."));
        return OutSpawns;
    }

    const FString RowName = UEnum::GetValueAsString(Construct);
    const FConstructRosterRow* Row = RosterTable->FindRow<FConstructRosterRow>(*RowName, TEXT("ConstructRoster"));
    if (!Row || Row->Units.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("[Roster] No units for construct: %s"), *RowName);
        return OutSpawns;
    }

    // Weighted pool: expand weights into an index list (PoC-grade, no alloc churn concerns at this scale).
    TArray<int32> Pool;
    Pool.Reserve(Row->Units.Num()); // at least; exact size after expansion
    for (int32 i = 0; i < Row->Units.Num(); ++i)
    {
        const int32 W = FMath::Max(1, FMath::RoundToInt(Row->Units[i].SpawnWeight));
        for (int32 k = 0; k < W; ++k) Pool.Add(i);
    }

    for (int32 i = 0; i < SpawnCount; ++i)
    {
        const FNetPRosterUnit& Unit = Row->Units[Pool[FMath::RandRange(0, Pool.Num() - 1)]];

        // ZETA-capped base roll (single source of truth for tiers), then stamp roster identity.
        FR3ALN3TNetPStatus NetP = UNetPRandomizer::RandomizeNetP();
        NetP.Construct   = Unit.Construct;
        NetP.FactionLean = Unit.FactionLean;
        if (Unit.Element != EElement::None) NetP.Element = Unit.Element; // None => keep randomizer's canon pick

        OutSpawns.Add(NetP);
    }

    return OutSpawns;
}

void UR3ALN3T_BattleManager::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    // ChipDB is fetched lazily in BeginEncounter/PlayChip so we don't depend on
    // subsystem init order here.
}

// ---- Legacy Phase2 (unchanged) ----
void UR3ALN3T_BattleManager::StartBattle(APlayerController* Player, const TArray<FVirusDef>& Enemies)
{
    if (bInBattle) return;
    bInBattle = true;
    BattlePlayer = Player;
    CurrentEnemies = Enemies;

    UE_LOG(LogTemp, Log, TEXT("Battle started with %d enemies"), Enemies.Num());
    OnBattleStart.Broadcast();
}

void UR3ALN3T_BattleManager::EndBattle(bool bPlayerWon)
{
    if (!bInBattle) return;
    bInBattle = false;

    PendingResult = FBattleResult();
    PendingResult.bPlayerWon = bPlayerWon;
    CalculateRewards();

    OnBattleEnd.Broadcast(PendingResult);
    UE_LOG(LogTemp, Log, TEXT("Battle ended. Player %s. Earned %d Z."),
        bPlayerWon ? TEXT("won") : TEXT("lost"), PendingResult.ZEarned);
}

void UR3ALN3T_BattleManager::CalculateRewards()
{
    if (!PendingResult.bPlayerWon) return;

    for (const auto& Virus : CurrentEnemies)
    {
        PendingResult.ZEarned += Virus.ZReward;
        PendingResult.EnemiesDefeated++;
        PendingResult.XP_Earned += 10 + Virus.HP / 10;

        if (FMath::FRand() <= Virus.DropRate && Virus.ChipDrops.Num() > 0)
        {
            int32 Index = FMath::RandRange(0, Virus.ChipDrops.Num() - 1);
            PendingResult.ChipsEarned.Add(Virus.ChipDrops[Index]);
        }
    }
}

// ---- Gap B: grid placement + chip resolution ----
void UR3ALN3T_BattleManager::BeginEncounter(const TArray<FEnemyDef>& Enemies)
{
    EnemySlots.Empty();

    // Lazy-fetch ChipDB from the GameInstance (this is a subsystem, so GetGameInstance() is valid).
    if (!ChipDB)
    {
        if (UGameInstance* GI = GetGameInstance())
        {
            ChipDB = GI->GetSubsystem<UChipDatabase>();
        }
        // Fallback: in some PIE/headless setups the subsystem may not be ready; build a transient
        // one so chip resolution always has data and the acceptance test can't silently 0-damage.
        if (!ChipDB)
        {
            ChipDB = NewObject<UChipDatabase>();
            ChipDB->PopulateSliceChips();
            UE_LOG(LogTemp, Warning, TEXT("BeginEncounter: ChipDatabase subsystem unavailable; using transient fallback."));
        }
    }

    PlaceEnemiesOnGrid(Enemies);

    // Presentation handoff (Isometric overworld -> 8x4 battle view) lives in whatever
    // owns camera/UI state and is OUT of Gap B scope. The data for it is ready here:
    // EnemySlots now describes exactly where each enemy sits on columns 4-7.
    OnBattleStart.Broadcast();
}

void UR3ALN3T_BattleManager::PlaceEnemiesOnGrid(const TArray<FEnemyDef>& Enemies)
{
    const int32 EnemyColumns[4] = { 4, 5, 6, 7 };
    const int32 MaxSliceEnemies = 4; // slice cap; widen later if grid supports more per column

    int32 SlotIndex = 0;
    for (const FEnemyDef& Def : Enemies)
    {
        if (SlotIndex >= MaxSliceEnemies)
        {
            UE_LOG(LogTemp, Warning, TEXT("PlaceEnemiesOnGrid: dropping enemy beyond slice cap of %d"), MaxSliceEnemies);
            break;
        }

        FGridEnemySlot Slot;
        Slot.Column = EnemyColumns[SlotIndex];
        Slot.Row = 0; // single row for the slice; multi-row placement is a post-slice concern
        Slot.EnemyDef = Def;
        Slot.CurrentHP = Def.HP; // FEnemyDef::HP is a stored field (verified formula lives in MakeEnemyDefFrom*)

        EnemySlots.Add(Slot);
        ++SlotIndex;
    }
}

const FGridEnemySlot* UR3ALN3T_BattleManager::FindSlotAt(int32 Column, int32 Row) const
{
    for (const FGridEnemySlot& Slot : EnemySlots)
    {
        if (Slot.Column == Column && Slot.Row == Row)
        {
            return &Slot;
        }
    }
    return nullptr;
}

FGridEnemySlot* UR3ALN3T_BattleManager::FindSlotAt(int32 Column, int32 Row)
{
    for (FGridEnemySlot& Slot : EnemySlots)
    {
        if (Slot.Column == Column && Slot.Row == Row)
        {
            return &Slot;
        }
    }
    return nullptr;
}

void UR3ALN3T_BattleManager::PlayChip(FName ChipCode, int32 TargetColumn, int32 TargetRow)
{
    if (!ChipDB)
    {
        UE_LOG(LogTemp, Error, TEXT("PlayChip: ChipDatabase not available"));
        return;
    }

    FGridEnemySlot* Target = FindSlotAt(TargetColumn, TargetRow);
    if (!Target || Target->CurrentHP <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayChip: no valid target at column %d row %d"), TargetColumn, TargetRow);
        return; // no valid target at that panel
    }

    // Element unification (G10) in effect: target's combat element is FEnemyDef::Element
    // (EBattleElementType, bridged from canon-21 EElement). ResolveChipDamage routes
    // through UElementWheelCalculator::ElementMultiplier (the canon-21 matrix) - NOT the
    // legacy 7-wheel EvaluateElementMultiplier, which is now dead code.
    const float Damage = ChipDB->ResolveChipDamage(ChipCode, Target->EnemyDef.Element);
    const int32 Before = Target->CurrentHP;
    Target->CurrentHP = FMath::Max(0, Target->CurrentHP - FMath::RoundToInt(Damage));

    // --- Gap C hook: one point of contact between combat and Soul State. ---
    // Fork intent = the chip's own SoulFork tag (None for the slice chips), classified
    // outcome is what would fire if no intent existed. We bias by the chip tag when present.
    ESoulFork Fork = (ChipDB->FindChip(ChipCode) && ChipDB->FindChip(ChipCode)->SoulFork != ESoulFork::None)
        ? ChipDB->FindChip(ChipCode)->SoulFork
        : ClassifyOutcome(Before, Target->CurrentHP);
    const float SoulShift = ApplyDamageFork(PlayerSoul, Before, Target->CurrentHP, Fork);

    UE_LOG(LogTemp, Log, TEXT("[GAPB-PIE] PlayChip %s vs %s: damage=%.1f (mult=%.2f), HP %d -> %d"),
        *ChipCode.ToString(), *UEnum::GetValueAsString(Target->EnemyDef.Element),
        Damage, ChipDB->ResolveChipDamage(ChipCode, Target->EnemyDef.Element) / FMath::Max(1.f, ChipDB->FindChip(ChipCode)->BasePower),
        Before, Target->CurrentHP);
    UE_LOG(LogTemp, Log, TEXT("[GAPC-PIE] Soul fork=%s shift=%.1f -> Soul %.1f (%s)"),
        *GetForkName(Fork), SoulShift, PlayerSoul.Soul, *PlayerSoul.GetBandName());
}

void UR3ALN3T_BattleManager::PlayChipConsole(const FString& ChipCodeStr, int32 TargetColumn, int32 TargetRow)
{
    PlayChip(FName(*ChipCodeStr), TargetColumn, TargetRow);
}

void UR3ALN3T_BattleManager::SoulForkConsole(const FString& ForkStr, const FString& ChipCodeStr, int32 TargetColumn, int32 TargetRow)
{
    const UEnum* E = StaticEnum<ESoulFork>();
    ESoulFork Fork = E ? static_cast<ESoulFork>(E->GetValueByNameString(ForkStr)) : ESoulFork::None;
    if (Fork == ESoulFork::None && !ForkStr.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("[GAPC-PIE] Unknown fork '%s'; falling back to outcome-classified fork."), *ForkStr);
    }
    // Force the fork by stashing it on a transient chip lookup is overkill; instead,
    // replicate PlayChip with a forced fork so the acceptance test can exercise all three.
    if (!ChipDB)
    {
        UE_LOG(LogTemp, Error, TEXT("SoulForkConsole: ChipDatabase not available"));
        return;
    }
    FGridEnemySlot* Target = FindSlotAt(TargetColumn, TargetRow);
    if (!Target || Target->CurrentHP <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("SoulForkConsole: no valid target at column %d row %d"), TargetColumn, TargetRow);
        return;
    }
    const float Damage = ChipDB->ResolveChipDamage(FName(*ChipCodeStr), Target->EnemyDef.Element);
    const int32 Before = Target->CurrentHP;
    Target->CurrentHP = FMath::Max(0, Target->CurrentHP - FMath::RoundToInt(Damage));

    const float SoulShift = ApplyDamageFork(PlayerSoul, Before, Target->CurrentHP, Fork);
    UE_LOG(LogTemp, Log, TEXT("[GAPB-PIE] PlayChip %s vs %s: damage=%.1f (mult=%.2f), HP %d -> %d"),
        *ChipCodeStr, *UEnum::GetValueAsString(Target->EnemyDef.Element),
        Damage, ChipDB->ResolveChipDamage(FName(*ChipCodeStr), Target->EnemyDef.Element) / FMath::Max(1.f, ChipDB->FindChip(FName(*ChipCodeStr))->BasePower),
        Before, Target->CurrentHP);
    UE_LOG(LogTemp, Log, TEXT("[GAPC-PIE] Soul fork=%s shift=%.1f -> Soul %.1f (%s)"),
        *GetForkName(Fork), SoulShift, PlayerSoul.Soul, *PlayerSoul.GetBandName());
}

void UR3ALN3T_BattleManager::SetSoul(float Value)
{
    PlayerSoul.Soul = FMath::Clamp(Value, 0.f, 100.f);
    UE_LOG(LogTemp, Log, TEXT("[GAPC-SEQ] SetSoul -> %.1f (%s)"), PlayerSoul.Soul, *PlayerSoul.GetBandName());
}

void UR3ALN3T_BattleManager::ResetTestEnemy()
{
    FGridEnemySlot* Target = FindSlotAt(4, 0);
    if (Target)
    {
        Target->CurrentHP = Target->EnemyDef.HP; // reseed from the def (no hardcoded HP)
        UE_LOG(LogTemp, Log, TEXT("[GAPC-SEQ] ResetTestEnemy (col4,row0) HP -> %d"), Target->CurrentHP);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("[GAPC-SEQ] ResetTestEnemy: no slot at (4,0)"));
    }
}

float UR3ALN3T_BattleManager::ApplyForcedFork(const FString& ForkStr, const FString& ChipCodeStr, int32 Col, int32 Row)
{
    const UEnum* E = StaticEnum<ESoulFork>();
    ESoulFork Fork = E ? static_cast<ESoulFork>(E->GetValueByNameString(ForkStr)) : ESoulFork::None;
    if (Fork == ESoulFork::None && !ForkStr.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("[GAPC-SEQ] Unknown fork '%s'; no shift."), *ForkStr);
        return 0.f;
    }
    if (!ChipDB)
    {
        UE_LOG(LogTemp, Error, TEXT("[GAPC-SEQ] ChipDatabase unavailable"));
        return 0.f;
    }
    FGridEnemySlot* Target = FindSlotAt(Col, Row);
    if (!Target || Target->CurrentHP <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("[GAPC-SEQ] no valid target at (%d,%d)"), Col, Row);
        return 0.f;
    }
    const float Damage = ChipDB->ResolveChipDamage(FName(*ChipCodeStr), Target->EnemyDef.Element);
    const int32 Before = Target->CurrentHP;
    Target->CurrentHP = FMath::Max(0, Target->CurrentHP - FMath::RoundToInt(Damage));
    return ApplyDamageFork(PlayerSoul, Before, Target->CurrentHP, Fork);
}

void UR3ALN3T_BattleManager::RunSoulSequence(float Baseline, const FString& ForkStr, int32 Count)
{
    SetSoul(Baseline);
    UE_LOG(LogTemp, Log, TEXT("[GAPC-SEQ] START baseline=%.1f (%s) fork=%s count=%d"),
        PlayerSoul.Soul, *PlayerSoul.GetBandName(), *ForkStr, Count);
    for (int32 i = 0; i < Count; ++i)
    {
        ResetTestEnemy();
        const float Shift = ApplyForcedFork(ForkStr, TEXT("Alpha"), 4, 0);
        UE_LOG(LogTemp, Log, TEXT("[GAPC-SEQ] step %2d  fork=%-7s shift=%+.1f -> Soul %5.1f (%s)"),
            i + 1, *ForkStr, Shift, PlayerSoul.Soul, *PlayerSoul.GetBandName());
    }
    UE_LOG(LogTemp, Log, TEXT("[GAPC-SEQ] END Soul=%.1f (%s)"), PlayerSoul.Soul, *PlayerSoul.GetBandName());
}

void UR3ALN3T_BattleManager::RunEnemySoulSequence(float Baseline, const FString& ForkStr)
{
	// Headless -game has no ChipDatabase, so resolve Alpha's known damage (120) inline
	// and drive both souls through ApplyDamageFork directly — no ChipDB dependency.
	const UEnum* E = StaticEnum<ESoulFork>();
	ESoulFork Fork = E ? static_cast<ESoulFork>(E->GetValueByNameString(ForkStr)) : ESoulFork::None;

	// Place a fresh test enemy at (4,0) so we own a slot to shift.
	FGridEnemySlot Slot;
	Slot.Column = 4; Slot.Row = 0;
	Slot.EnemyDef = FEnemyDef(); // default def; Element default is fine for the damage calc
	Slot.CurrentHP = 120;
	Slot.Soul.Soul = Baseline;
	// Replace or add the (4,0) slot.
	bool bReplaced = false;
	for (FGridEnemySlot& S : EnemySlots)
	{
		if (S.Column == 4 && S.Row == 0) { S = Slot; bReplaced = true; break; }
	}
	if (!bReplaced) EnemySlots.Add(Slot);

	PlayerSoul.Soul = FMath::Clamp(Baseline, 0.f, 100.f);
	UE_LOG(LogTemp, Log, TEXT("[GAPD-SEQ] START player=%.1f enemy=%.1f fork=%s"),
		PlayerSoul.Soul, Slot.Soul.Soul, *ForkStr);

	// One forced fork against the (4,0) enemy, shifting BOTH souls (Alpha = 120 dmg).
	const int32 Before = 120;
	const int32 After = 40; // survived (Spare/Purge don't kill 120->40)
	const float PS = ApplyDamageFork(PlayerSoul, Before, After, Fork);

	FGridEnemySlot* ES = FindSlotAt(4, 0);
	if (ES)
	{
		const float ES_ = ApplyDamageFork(ES->Soul, Before, After, Fork);
		UE_LOG(LogTemp, Log, TEXT("[GAPD-SEQ] player shift=%+.1f -> %.1f (%s) | enemy shift=%+.1f -> %.1f (%s)"),
			PS, PlayerSoul.Soul, *PlayerSoul.GetBandName(),
			ES_, ES->Soul.Soul, *ES->Soul.GetBandName());
	}
}

void UR3ALN3T_BattleManager::RunSoulKillSequence(float Baseline, const FString& ForkStr)
{
    SetSoul(Baseline);
    ResetTestEnemy(); // start the (4,0) enemy at full HP (120)
    UE_LOG(LogTemp, Log, TEXT("[GAPC-SEQ] KILLSTART baseline=%.1f (%s) fork=%s"),
        PlayerSoul.Soul, *PlayerSoul.GetBandName(), *ForkStr);

    // Hit 1: 120 -> 40 (survives). Capture the survive-branch delta.
    const float SurviveShift = ApplyForcedFork(ForkStr, TEXT("Alpha"), 4, 0);
    UE_LOG(LogTemp, Log, TEXT("[GAPC-SEQ] KILL hit1 survive shift=%+.1f -> Soul %.1f (%s)"),
        SurviveShift, PlayerSoul.Soul, *PlayerSoul.GetBandName());

    // Hit 2: 40 -> 0 (dies). No reseed -> exercises the live death branch.
    const float KillShift = ApplyForcedFork(ForkStr, TEXT("Alpha"), 4, 0);
    UE_LOG(LogTemp, Log, TEXT("[GAPC-SEQ] KILL hit2 kill    shift=%+.1f -> Soul %.1f (%s)"),
        KillShift, PlayerSoul.Soul, *PlayerSoul.GetBandName());

    UE_LOG(LogTemp, Log, TEXT("[GAPC-SEQ] KILLEND survive=%+.1f kill=%+.1f finalSoul=%.1f (%s)"),
        SurviveShift, KillShift, PlayerSoul.Soul, *PlayerSoul.GetBandName());
}

void UR3ALN3T_BattleManager::RunSoulSequenceMixed(float Baseline)
{
    static const TCHAR* Seq[] = {
        TEXT("Spare"), TEXT("Spare"), TEXT("Purge"), TEXT("Corrupt"), TEXT("Spare"),
        TEXT("Purge"), TEXT("Corrupt"), TEXT("Corrupt"), TEXT("Spare"), TEXT("Purge")
    };
    SetSoul(Baseline);
    UE_LOG(LogTemp, Log, TEXT("[GAPC-SEQ] START baseline=%.1f (%s) fork=mixed count=%d"),
        PlayerSoul.Soul, *PlayerSoul.GetBandName(), UE_ARRAY_COUNT(Seq));
    for (int32 i = 0; i < UE_ARRAY_COUNT(Seq); ++i)
    {
        const TCHAR* S = Seq[i];
        ResetTestEnemy();
        const float Shift = ApplyForcedFork(S, TEXT("Alpha"), 4, 0);
        UE_LOG(LogTemp, Log, TEXT("[GAPC-SEQ] step %2d  fork=%-7s shift=%+.1f -> Soul %5.1f (%s)"),
            i + 1, S, Shift, PlayerSoul.Soul, *PlayerSoul.GetBandName());
    }
    UE_LOG(LogTemp, Log, TEXT("[GAPC-SEQ] END Soul=%.1f (%s)"), PlayerSoul.Soul, *PlayerSoul.GetBandName());
}

void UR3ALN3T_BattleManager::RunSoulRoundTrip(float PlayerSoulValue, float TrinityValue, float TyrannyValue, float EternityValue)
{
    // Gap D persistence test: write souls into the run, SAVE, LOAD into a fresh in-memory
    // run, and log the round-tripped values so the verify script can assert save==load.
    UR3ALN3TGameInstance* GI = Cast<UR3ALN3TGameInstance>(GetGameInstance());
    if (!GI)
    {
        UE_LOG(LogTemp, Error, TEXT("[GAPD-SAVE] GameInstance unavailable; cannot round-trip."));
        return;
    }

    // 1) Seed the run with the requested values.
    GI->CurrentRun.PlayerSoul.Soul = FMath::Clamp(PlayerSoulValue, 0.f, 100.f);
    GI->CurrentRun.NetPSouls.Empty();
    struct FSeed { FString Name; float Val; };
    const FSeed Seeds[] = {
        { TEXT("Trinity"), TrinityValue },
        { TEXT("Tyranny"),  TyrannyValue },
        { TEXT("Eternity"), EternityValue }
    };
    for (const FSeed& Seed : Seeds)
    {
        FCompanionSoul C;
        C.NetPID = FName(*Seed.Name);
        C.Soul.Soul = FMath::Clamp(Seed.Val, 0.f, 100.f);
        GI->CurrentRun.NetPSouls.Add(C);
    }

    // 2) Save to slot 0.
    GI->SaveGame(0);

    // 3) Mutate the live run so a no-op load would be detectable, then LOAD back.
    GI->CurrentRun.PlayerSoul.Soul = -999.f;
    GI->CurrentRun.NetPSouls.Empty();
    const bool bLoaded = GI->LoadGame(0);

    // 4) Log the round-tripped state.
    if (!bLoaded)
    {
        UE_LOG(LogTemp, Error, TEXT("[GAPD-SAVE] LoadGame(0) FAILED — round-trip broken."));
        return;
    }
    float RTPlayer = GI->CurrentRun.PlayerSoul.Soul;
    FString RTSouls;
    for (const FCompanionSoul& C : GI->CurrentRun.NetPSouls)
    {
        RTSouls += FString::Printf(TEXT("%s=%.1f(%s) "), *C.NetPID.ToString(), C.Soul.Soul, *C.Soul.GetBandName());
    }
    UE_LOG(LogTemp, Log, TEXT("[GAPD-SAVE] SAVE player=%.1f T/Ty/E=%.1f/%.1f/%.1f -> LOAD player=%.1f %s"),
        PlayerSoulValue, TrinityValue, TyrannyValue, EternityValue, RTPlayer, *RTSouls);
}

bool UR3ALN3T_BattleManager::IsEncounterCleared() const
{
    if (EnemySlots.Num() == 0) return false;
    for (const FGridEnemySlot& Slot : EnemySlots)
    {
        if (Slot.CurrentHP > 0)
        {
            return false;
        }
    }
    return true;
}

int32 UR3ALN3T_BattleManager::GetEnemyCurrentHP(int32 Column, int32 Row) const
{
    if (const FGridEnemySlot* Slot = FindSlotAt(Column, Row))
    {
        return Slot->CurrentHP;
    }
    return -1;
}
