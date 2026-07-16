// EncounterTriggerComponent.h
// Attached to player character. Detects zone-based random encounters.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "R3ALN3T_BattleManager.h" // FVirusDef, EBattleElementType (defined here, not in CombatTypes.h)
#include "EncounterTriggerComponent.generated.h"

class UWorldLayerManager;
class UR3ALN3T_BattleManager;
struct FVirusDef;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class R3ALN3T_UE5_API UEncounterTriggerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UEncounterTriggerComponent();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Encounter")
    float StepInterval = 0.5f; // Check every 0.5 seconds of movement

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Encounter")
    float MinMoveThreshold = 50.0f; // Must move 50cm since last check

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Encounter")
    TArray<FVirusDef> CommonViruses;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Encounter")
    TArray<FVirusDef> Sector2Viruses;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Encounter")
    TArray<FVirusDef> Sector3Viruses;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Encounter")
    TArray<FVirusDef> BossViruses;

    // PIE / acceptance-test seam: when true, fire ONE deterministic Aqua-grunt encounter
    // on BeginPlay instead of the random walk-roll. Keeps the production random path intact.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Encounter|Test")
    bool bForceEncounterOnStart = false;

    // Hardcoded test enemy used only when bForceEncounterOnStart is set (Aqua = super-effective vs Fire).
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Encounter|Test")
    FVirusDef ForcedTestVirus = { TEXT("VIRUS_FISH"), FText::FromString(TEXT("Fishy Grunt")), 120, 8, 0, 10, { TEXT("Bubble") }, 0.25f, EBattleElementType::Aqua };

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    float TimeSinceLastStep = 0.0f;
    FVector LastLocation;
    UWorldLayerManager* LayerManager;
    UR3ALN3T_BattleManager* BattleManager;
    APlayerController* PlayerController;

    void TryEncounter(FVector CurrentLocation);
    TArray<FVirusDef> PickVirusList(const FString& ZoneTag);

    // Forces a single deterministic encounter immediately (used for PIE acceptance test).
    UFUNCTION(BlueprintCallable, Category = "Encounter|Test")
    void ForceEncounter();

    // Chapter 5.3: stash the player's current world location into UR3ALSaveGame, then
    // transition to the battle level (Rotterdam_PoC). Used by both random and forced paths.
    UFUNCTION(BlueprintCallable, Category = "Encounter")
    void TransitionToBattle();
};
