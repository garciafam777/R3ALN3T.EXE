// EncounterTriggerComponent.h
// Attached to player character. Detects zone-based random encounters.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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
};
