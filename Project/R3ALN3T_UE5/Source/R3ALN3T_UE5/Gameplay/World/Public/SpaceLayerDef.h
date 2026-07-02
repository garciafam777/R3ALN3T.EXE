// SpaceLayerDef.h
// Outer space and Luna/Mars layer definitions
#pragma once
#include "CoreMinimal.h"
#include "SpaceLayerDef.generated.h"

USTRUCT(BlueprintType)
struct FSpaceStationPOI
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere) FVector OrbitCenter;
    UPROPERTY(EditAnywhere) FString Name;
    UPROPERTY(EditAnywhere) FString Type; // FreighterYard, HabitatRing, WarpJunction
    UPROPERTY(EditAnywhere) float OrbitRadius = 3000.0f;
};

USTRUCT(BlueprintType)
struct FColonyPOI
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere) FVector Location;
    UPROPERTY(EditAnywhere) FString Name;
    UPROPERTY(EditAnywhere) FString Type; // BioDome, SubsurfaceHabitat, MiningExtraction
    UPROPERTY(EditAnywhere) bool bOnMars = true;
};
