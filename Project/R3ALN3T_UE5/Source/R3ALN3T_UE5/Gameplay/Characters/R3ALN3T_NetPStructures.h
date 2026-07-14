#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "../World/R3ALN3T_WorldStructures.h"
#include "../../Core/Types/SoulState.h"   // Gap D: FSoulState for companion souls
#include "R3ALN3T_NetPStructures.generated.h"

UENUM(BlueprintType)
enum class ENetPArchetype : uint8
{
    // --- 5 existing ---
    Vanguard      UMETA(DisplayName = "Vanguard Daemon"),
    LogicGate     UMETA(DisplayName = "Logic Gate Keeper"),
    Infiltrator   UMETA(DisplayName = "Ghost Infiltrator"),
    SentientNode  UMETA(DisplayName = "Sentient AI Node"),
    Wraith        UMETA(DisplayName = "Void Wraith"),
    // --- 11 design archetypes (Option B add; CEO: apply all listed) ---
    Trucker       UMETA(DisplayName = "Trucker"),
    ATC           UMETA(DisplayName = "ATC"),
    Medical       UMETA(DisplayName = "Medical"),
    Construction  UMETA(DisplayName = "Construction"),
    Cipher        UMETA(DisplayName = "Cipher"),
    Cognition     UMETA(DisplayName = "Cognition"),
    DataCenter    UMETA(DisplayName = "Data Center"),
    Factory       UMETA(DisplayName = "Factory"),
    Lab           UMETA(DisplayName = "Lab"),
    Civic         UMETA(DisplayName = "Civic"),
    Orbital       UMETA(DisplayName = "Orbital")
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

// Gap D: a companion's persistent soul. One per NetP (Trinity / Tyranny / Eternity),
// stored in FPersistentRunData::NetPSouls (UR3ALN3TGameInstance::CurrentRun.NetPSouls)
// so it round-trips through SaveGame/LoadGame. The run's mythos state lives separately
// in FMythosRunState (FPersistentRunData::RunState). The transient battle-enemy soul
// (FGridEnemySlot::Soul) is separate and NOT saved.
USTRUCT(BlueprintType)
struct FCompanionSoul
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soul")
    FName NetPID;            // e.g. "Trinity", "Tyranny", "Eternity"

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soul")
    FSoulState Soul;         // 0-100, band via Soul.GetBand()
};
