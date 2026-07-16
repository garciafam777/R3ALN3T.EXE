// R3ALN3T_UE5 GameInstance Integration: Phase 2 Core
// Player state, progression tracking, battle rewards
//
// Gap B additions (2026-07-08): grid placement of FEnemyDef + chip resolution through
// the verified EvaluateElementMultiplier. Design boundary per Architecture_Overview.md:
// "enemy spawning" = battle-grid placement on cols 4-7, NOT an overworld actor spawn.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "../../Core/Types/MythosGameTypes.h"
#include "../../Core/Types/CombatTypes.h" // FEnemyDef, EEnemySource
#include "../../Core/Types/SoulState.h"   // Gap C: FSoulState, ESoulFork
#include "R3ALN3T_BattleManager.generated.h"

class ABattleGridManager;
class APlayerController;
// Forward-declared to avoid a CombatTypes.h <-> ChipDatabase.h circular include.
// (CombatTypes.h pulls in R3ALN3T_BattleManager.h; ChipDatabase.h pulls in CombatTypes.h.)
class UChipDatabase;

USTRUCT(BlueprintType)
struct FVirusDef
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName VirusID = NAME_None;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText DisplayName = FText::GetEmpty();
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 HP = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Attack = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Shield = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ZReward = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> ChipDrops;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float DropRate = 0.f;
    // ADDED for Gap B acceptance test: lets a Fire chip land x2.0 on an Aqua virus.
    // Defaults to None (neutral) so existing code is unaffected.
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EBattleElementType Element = EBattleElementType::None;
};

USTRUCT(BlueprintType)
struct FBattleResult
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly) bool bPlayerWon = false;
    UPROPERTY(BlueprintReadOnly) int32 ZEarned = 0;
    UPROPERTY(BlueprintReadOnly) TArray<FName> ChipsEarned;
    UPROPERTY(BlueprintReadOnly) int32 XP_Earned = 0;
    UPROPERTY(BlueprintReadOnly) int32 EnemiesDefeated = 0;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBattleStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBattleEnd, FBattleResult, Result);

// One placed enemy on the 8x4 grid (enemy columns 4-7).
USTRUCT()
struct FGridEnemySlot
{
    GENERATED_BODY()

    UPROPERTY() int32 Column = 4; // 4-7 = enemy side
    UPROPERTY() int32 Row = 0;    // 0-3
    UPROPERTY() FEnemyDef EnemyDef;
    UPROPERTY() int32 CurrentHP = 0;
    UPROPERTY() FSoulState Soul; // Gap D: transient enemy soul (not saved; re-rolled each battle)
};

// UCLASS rebase: UGameInstanceSubsystem (was UObject) so the trigger and any system can
// reach it via GetGameInstance()->GetSubsystem<UR3ALN3T_BattleManager>() and fetch ChipDB.
UCLASS(BlueprintType)
class R3ALN3T_UE5_API UR3ALN3T_BattleManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    // Legacy (Phase 2) entry — kept intact.
    UFUNCTION(BlueprintCallable, Category = "Battle")
    void StartBattle(APlayerController* Player, const TArray<FVirusDef>& Enemies);

    UFUNCTION(BlueprintCallable, Category = "Battle")
    void EndBattle(bool bPlayerWon);

    UFUNCTION(BlueprintCallable, Category = "Battle")
    bool IsInBattle() const { return bInBattle; }

    UPROPERTY(BlueprintAssignable) FOnBattleStart OnBattleStart;
    UPROPERTY(BlueprintAssignable) FOnBattleEnd OnBattleEnd;

    // ---- Gap B seam ----
    // Called by EncounterTriggerComponent when a walk-triggered encounter resolves.
    // This is the only place "spawning" happens: enemies are placed on the grid,
    // never spawned as world actors.
    UFUNCTION(BlueprintCallable, Category = "Battle|GapB")
    void BeginEncounter(const TArray<FEnemyDef>& Enemies);

    // Resolves a chip play from the active folder slot against a grid target.
    UFUNCTION(BlueprintCallable, Category = "Battle|GapB")
    void PlayChip(FName ChipCode, int32 TargetColumn, int32 TargetRow);

    // PIE acceptance-test command: run `PlayChipConsole Alpha 4 0` from the console to
    // resolve a chip and watch CurrentHP drop in the log. Mirrors PlayChip with logging.
    // Called from the possessed test pawn's Exec handler (console). Not itself an Exec:
    // a UGameInstanceSubsystem Exec handler is never reached from the PIE console.
    UFUNCTION(BlueprintCallable, Category = "Battle|GapB")
    void PlayChipConsole(const FString& ChipCodeStr, int32 TargetColumn, int32 TargetRow);

    // Gap C acceptance-test command: same as PlayChipConsole but forces a soul fork
    // (override), e.g. `SoulForkConsole Corrupt Alpha 4 0`. Lets a single PIE run
    // exercise all three outcomes (Spare/Purge/Corrupt) regardless of chip tags.
    UFUNCTION(BlueprintCallable, Category = "Battle|GapC")
    void SoulForkConsole(const FString& ForkStr, const FString& ChipCodeStr, int32 TargetColumn, int32 TargetRow);

    // Gap C tuning harness (console-driven): set the player-soul baseline directly so a
    // sequence can start from a known value, and reseed the (4,0) test enemy to full HP so
    // a fork sequence can repeat. Lets band-feel be explored cheaply before persistence/
    // visuals are built on top of these numbers.
    UFUNCTION(BlueprintCallable, Category = "Battle|GapC")
    void SetSoul(float Value);
    UFUNCTION(BlueprintCallable, Category = "Battle|GapC")
    void ResetTestEnemy();
    // Runs Fork Count times from Baseline (reseed enemy each step -> SURVIVE branch).
    // Primitives only so UE exec parses it cleanly: e.g. `RunSoulSequence 50 Spare 10`
    UFUNCTION(BlueprintCallable, Category = "Battle|GapC")
    void RunSoulSequence(float Baseline, const FString& ForkStr, int32 Count);
    // Fixed realistic mixed session (Spare,Spare,Purge,Corrupt,Spare,Purge,Corrupt,Corrupt,Spare,Purge) from Baseline.
    UFUNCTION(BlueprintCallable, Category = "Battle|GapC")
    void RunSoulSequenceMixed(float Baseline);
    // Kill-branch test: from Baseline, hit the (4,0) enemy twice with Alpha (120->40->0) so
    // the 2nd hit KILLS it -> exercises the live death branch. Logs both survive(-hit1) and
    // kill(-hit2) deltas so Spare-kill (-2) / Purge-kill (-6) can be verified against real kills.
    UFUNCTION(BlueprintCallable, Category = "Battle|GapC")
    void RunSoulKillSequence(float Baseline, const FString& ForkStr);

    // Gap D acceptance-test command: place a fresh test enemy, set baseline player+enemy soul,
    // run one forced fork, and log BOTH the player soul shift AND the enemy soul shift so the
    // enemy-soul mechanic can be verified against a real -game launch.
    // e.g. `RunEnemySoulSequence 50 Spare`  (player & enemy both start at 50)
    UFUNCTION(BlueprintCallable, Category = "Battle|GapD")
    void RunEnemySoulSequence(float Baseline, const FString& ForkStr);

    // Gap D persistence test: seed player + 3 NetP souls, SaveGame(0), mutate live run,
    // LoadGame(0), and log the round-tripped values so save==load is assertable.
    // e.g. `RunSoulRoundTrip 50 70 30 85`
    UFUNCTION(BlueprintCallable, Category = "Battle|GapD")
    void RunSoulRoundTrip(float PlayerSoulValue, float TrinityValue, float TyrannyValue, float EternityValue);

    // True once all enemy slots report CurrentHP <= 0.
    UFUNCTION(BlueprintPure, Category = "Battle|GapB")
    bool IsEncounterCleared() const;

    UFUNCTION(BlueprintPure, Category = "Battle|GapB")
    int32 GetEnemyCurrentHP(int32 Column, int32 Row) const;

private:
    bool bInBattle = false;
    TArray<FVirusDef> CurrentEnemies;
    APlayerController* BattlePlayer = nullptr;
    TArray<FGridEnemySlot> EnemySlots;       // Gap B grid state
    UChipDatabase* ChipDB = nullptr;         // fetched lazily from GameInstance
    FSoulState PlayerSoul;                   // Gap C: single player soul state
    void CalculateRewards();
    FBattleResult PendingResult;

    // Gap B: places incoming enemies across columns 4-7, one per column, capped at 4 for the slice.
    void PlaceEnemiesOnGrid(const TArray<FEnemyDef>& Enemies);

    // ---- Faction/Construct Roster seam ----
    // Data-driven: given a bound roster DataTable (rows keyed by ENetPConstruct name:
    // "Trinity"/"Tyranny"/"Eternity", each FConstructRosterRow), roll SpawnCount NetPs
    // for the active construct. Each NetP is ZETA-capped via UNetPRandomizer, then stamped
    // with the roster unit's Construct/Element/FactionLean identity. Caller feeds the
    // results into ABattleGridManager::TryPlaceNetPAtCell (col 4-7 gate + ZETA clamp).
    // Returns empty if Table is null or the construct has no row/units.
    UFUNCTION(BlueprintCallable, Category = "Battle|Roster")
    TArray<FR3ALN3TNetPStatus> GenerateConstructSpawns(UDataTable* RosterTable, ENetPConstruct Construct, int32 SpawnCount) const;

    // Golden-Loop integration entry point. Rolls ConstructRoster (data-driven), pipes each
    // NetP through ABattleGridManager::TryPlaceNetPAtCell (col 4-7 gate + ZETA clamp), and
    // resolves its card frame via UNetPCardViewModel. BeginEncounter(const TArray<FEnemyDef>&)
    // (Gap B) is unchanged; callers that want the roster seam use this instead.
    UFUNCTION(BlueprintCallable, Category = "Battle|Roster")
    void BeginConstructEncounter(UDataTable* RosterTable, UDataTable* FrameTable, ENetPConstruct Construct, int32 EnemyCount);

    // Console-driven Golden-Loop test entry (mirrors PlayChipConsole). Loads the two DTs by
    // their fixed /Game/... asset paths at call time, so no editor property binding is required.
    // e.g. `BeginConstructEncounterConsole Trinity 3` from the PIE console.
    UFUNCTION(Exec, Category = "Battle|Roster")
    void BeginConstructEncounterConsole(FString FactionName, int32 EnemyCount);

    // New callback to execute the Golden Loop automatically when the CVar is set
    void OnWorldBeginPlay_AutoFireGoldenLoop(UWorld* World, const UWorld::InitializationValues IVS);

    FGridEnemySlot* FindSlotAt(int32 Column, int32 Row);
    const FGridEnemySlot* FindSlotAt(int32 Column, int32 Row) const;

    // Gap C tuning harness: apply a forced fork against the (Col,Row) target. The caller
    // is responsible for reseeding the enemy if a repeatable sequence is wanted. Returns shift.
    float ApplyForcedFork(const FString& ForkStr, const FString& ChipCodeStr, int32 Col, int32 Row);
};
