// RealityWorldBuilder.h
// Spawns the R3AL World blockout: roads, buildings, grid sectors, encounter zones, NPC points.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RealityWorldBuilder.generated.h"

class UWorldLayerManager;

USTRUCT(BlueprintType)
struct FRoadSegment
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere) FVector Start;
    UPROPERTY(EditAnywhere) FVector End;
    UPROPERTY(EditAnywhere) float Width = 500.0f;
};

USTRUCT(BlueprintType)
struct FBuildingPlot
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere) FVector Location;
    UPROPERTY(EditAnywhere) FVector Extent = FVector(600, 400, 250);
    UPROPERTY(EditAnywhere) FString BuildingType = TEXT("residential");
};

USTRUCT(BlueprintType)
struct FGridSectorDef
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere) FString SectorID;
    UPROPERTY(EditAnywhere) FVector Location;
    UPROPERTY(EditAnywhere) float Radius = 3000.0f;
    UPROPERTY(EditAnywhere) int32 VirusLevel = 1;
};

UCLASS()
class R3ALN3T_UE5_API ARealityWorldBuilder : public AActor
{
    GENERATED_BODY()

public:
    ARealityWorldBuilder();
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World")
    TArray<FRoadSegment> RoadNetwork;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World")
    TArray<FBuildingPlot> BuildingPlots;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World")
    TArray<FGridSectorDef> GridSectors;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World")
    UStaticMesh* RoadMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World")
    UStaticMesh* BuildingMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World")
    UMaterialInterface* RoadMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World")
    UMaterialInterface* BuildingMaterial;

    UFUNCTION(BlueprintCallable, Category = "World")
    void BuildWorld();

    UFUNCTION(BlueprintCallable, Category = "World")
    void ClearWorld();

    UFUNCTION(BlueprintCallable, Category = "World")
    void RegisterEncounterZones(UWorldLayerManager* Manager);

private:
    UPROPERTY()
    TArray<AActor*> SpawnedActors;

    void SpawnRoad(const FRoadSegment& Segment);
    void SpawnBuilding(const FBuildingPlot& Plot);
};
