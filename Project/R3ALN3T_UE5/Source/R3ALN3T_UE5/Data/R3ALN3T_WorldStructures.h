#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "R3ALN3T_WorldStructures.generated.h"

UENUM(BlueprintType)
enum class ER3ALN3TLayer : uint8
{
    Heaven              UMETA(DisplayName = "Heaven"),
    OuterSpace          UMETA(DisplayName = "Outer Space"),
    LunaMars            UMETA(DisplayName = "Luna / Mars"),
    Reality             UMETA(DisplayName = "R3AL World"),
    Cyberspace          UMETA(DisplayName = "Cyberspace Mirror"),
    Hell                UMETA(DisplayName = "Hell")
};

USTRUCT(BlueprintType)
struct FR3ALN3TWorldAssetRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Metrics")
    FString AssetID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Metrics")
    ER3ALN3TLayer TargetLayer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asset Pointers")
    TSoftObjectPtr<UStaticMesh> StaticMeshRef;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Metrics")
    FVector DefaultScaleOverride = FVector(1.0f, 1.0f, 1.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
    bool bEnableNanite = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
    bool bForceCustomComplexCollision = false;
};
