// GrayBox_isolation_manifest.h
// Frozen design contract for the isolated gray-box second-map module.
// Do not include this from shared C++ classes or shared maps.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GrayBoxIsolatedSecondMap.generated.h"

UENUM(BlueprintType)
enum class EIsolationRegion : uint8
{
    TaxiKingdom UMETA(DisplayName="Taxi Kingdom"),
    LunaMars Perimeter UMETA(DisplayName="Luna/Mars Perimeter"),
    HeavenGate UMETA(DisplayName="Heaven Gate"),
    HellFoundry UMETA(DisplayName="Hell Foundry"),
    DeepN3T UMETA(DisplayName="Deep N3T")
};

USTRUCT(BlueprintType)
struct FIsolatedZoneManifestRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ZoneID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EIsolationRegion Region;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName LockedLayerTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText FlavorText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Budget = 64;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MiniGridSize = 8;
};

USTRUCT(BlueprintType)
struct FTaxiSpawnParcel
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName NodeID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector GridParcelMin;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector GridParcelMax;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName BuildingSet = "Courthouse";

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName RoadClass = "PedestrianRibbon";
};
