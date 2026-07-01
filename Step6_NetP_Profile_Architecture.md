# Step6_NetP_Profile_Architecture.md
## R3ALN3T.EXE: NetP Character Profile Architecture

Pinokio must write this block directly to Source/R3ALN3T/Public/R3ALN3T_NetPStructures.h:
#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "R3ALN3T_NetPStructures.generated.h"

UENUM(BlueprintType)
enum class ENetPArchetype : uint8 { Vanguard, LogicGate, Infiltrator, SentientNode, Wraith };

USTRUCT(BlueprintType)
struct FR3ALN3TNetPProfileRow : public FTableRowBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName NetPID;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText DisplayName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) ENetPArchetype Archetype = ENetPArchetype::LogicGate;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector BaselineSpawnOffset = FVector(0.0f, 0.0f, 0.0f);
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 BaseProcessingLevel = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float BaseThroughputSpeed = 300.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TSoftObjectPtr<USkeletalMesh> CharacterMeshOverride;
};
