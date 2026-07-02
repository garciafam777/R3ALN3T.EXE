// HeavenLayerDef.h
// Heaven layer visual data structures
#pragma once
#include "CoreMinimal.h"
#include "HeavenLayerDef.generated.h"

USTRUCT(BlueprintType)
struct FHeavenPOI
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere) FVector Location;
    UPROPERTY(EditAnywhere) FString Name;
    UPROPERTY(EditAnywhere) FString Type; // EmpyreanAscent, NimbusPalace, AuroraFalls, WhisperwindArchive, GoldenGate
    UPROPERTY(EditAnywhere) float LightBeamHeight = 5000.0f;
};
