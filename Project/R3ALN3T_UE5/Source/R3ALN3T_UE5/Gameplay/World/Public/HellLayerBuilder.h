// HellLayerBuilder.h
// Procedural hell layer builder - volcanic rock, lava rivers, corrupted architecture
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../../Gameplay/World/Public/WorldLayerManager.h"
#include "HellLayerBuilder.generated.h"

UCLASS()
class R3ALN3T_UE5_API AHellLayerBuilder : public AActor
{
    GENERATED_BODY()
public:
    AHellLayerBuilder();
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hell")
    TArray<FVector> LavaRiverPoints;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hell")
    TArray<FVector> ObsidianSpireLocations;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hell")
    TArray<FEncounterZone> HellEncounterZones;

    UFUNCTION(BlueprintCallable, Category = "Hell")
    void BuildHellscape();

    void RegisterZones(UWorldLayerManager* Manager);

private:
    void SpawnLavaRiver(FVector Start, FVector End);
    void SpawnObsidianSpire(FVector Location);
};
