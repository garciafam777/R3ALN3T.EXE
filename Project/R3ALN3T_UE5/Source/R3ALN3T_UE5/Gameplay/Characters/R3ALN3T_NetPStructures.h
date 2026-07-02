#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "../World/R3ALN3T_WorldStructures.h"
#include "R3ALN3T_NetPStructures.generated.h"

UENUM(BlueprintType)
enum class ENetPArchetype : uint8
{
    Vanguard      UMETA(DisplayName = "Vanguard Daemon"),
    LogicGate     UMETA(DisplayName = "Logic Gate Keeper"),
    Infiltrator   UMETA(DisplayName = "Ghost Infiltrator"),
    SentientNode  UMETA(DisplayName = "Sentient AI Node"),
    Wraith        UMETA(DisplayName = "Void Wraith")
};

USTRUCT(BlueprintType)
struct FR3ALN3TNetPProfileRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    FName NetPID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classification")
    ENetPArchetype Archetype = ENetPArchetype::LogicGate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    ER3ALN3TLayer HomeDimension = ER3ALN3TLayer::Cyberspace;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    FVector BaselineSpawnOffset = FVector(0.0f, 0.0f, 0.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    int32 BaseProcessingLevel = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    float BaseThroughputSpeed = 300.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    float CoreStabilityIndex = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
    TSoftObjectPtr<USkeletalMesh> CharacterMeshOverride;
};
