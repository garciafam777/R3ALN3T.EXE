// CyberspaceDef.h
// Cyberspace mirror layer - grid floors, neon data streams, firewall gates
#pragma once
#include "CoreMinimal.h"
#include "CyberspaceDef.generated.h"

USTRUCT(BlueprintType)
struct FCyberspacePOI
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere) FVector Location;
    UPROPERTY(EditAnywhere) FString Name;
    UPROPERTY(EditAnywhere) FString Type; // DataConflux, FirewallCitadel, GlitchSpire, NeonNexus, AlgorithmGarden
    UPROPERTY(EditAnywhere) FLinearColor NeonColor = FLinearColor(0, 1, 1);
};
