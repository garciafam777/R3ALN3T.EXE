// GrayBoxPlayerPawn.h
// Minimal native pawn for the Gap A gray-box acceptance map. Constructor-attaches the
// EncounterTriggerComponent (so it needs no Python/Blueprint attach dance) and forces a
// deterministic encounter on BeginPlay. This is a TEST-ONLY pawn; real player pawns live
// elsewhere and wire the trigger differently.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GrayBoxPlayerPawn.generated.h"

class UEncounterTriggerComponent;

UCLASS()
class R3ALN3T_UE5_API AGrayBoxPlayerPawn : public APawn
{
    GENERATED_BODY()
public:
    AGrayBoxPlayerPawn();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GrayBox")
    UEncounterTriggerComponent* Trigger;

    // PIE test console command. Declared Exec on the PAWN (which gets possessed in PIE)
    // so it lands in the player controller's Exec routing chain — a UGameInstanceSubsystem
    // Exec handler is never reached from the console. Run e.g. `PlayChipConsole Alpha 4 0`.
    UFUNCTION(Exec)
    void PlayChipConsole(const FString& ChipCodeStr, int32 TargetColumn, int32 TargetRow);

    // Gap C tuning harness Execs (console): SetSoul, ResetTestEnemy, RunSoulSequence.
    UFUNCTION(Exec)
    void SetSoul(float Value);
    UFUNCTION(Exec)
    void ResetTestEnemy();
    UFUNCTION(Exec)
    void RunSoulSequence(float Baseline, const FString& ForkStr, int32 Count);
    UFUNCTION(Exec)
    void RunSoulSequenceMixed(float Baseline);
    UFUNCTION(Exec)
    void RunSoulKillSequence(float Baseline, const FString& ForkStr);

    // Gap C: force a soul fork from the PIE console, e.g. `SoulForkConsole Corrupt Alpha 4 0`.
    UFUNCTION(Exec)
    void SoulForkConsole(const FString& ForkStr, const FString& ChipCodeStr, int32 TargetColumn, int32 TargetRow);
};
