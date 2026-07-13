// GrayBoxIsolatedSecondMap.h
// Fully isolated second-zone gray-box source. No edits to shared classes.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrayBoxIsolatedSecondMap.generated.h"

class AGrayBox_Test;

USTRUCT(BlueprintType)
struct FTaxiNodeDef
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Taxi")
    FName NodeID = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Taxi")
    FText DisplayName = FText::GetEmpty();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Taxi")
    FVector WorldLocation = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Taxi")
    TSoftObjectPtr<UStaticMesh> RoadSegmentMeshRef;
};

UCLASS()
class R3ALN3T_EXE_API AGrayBoxIsolatedSecondMap : public AActor
{
    GENERATED_BODY()

public:
    AGrayBoxIsolatedSecondMap();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Taxi|Isolation")
    FName RegionID = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Taxi|Isolation")
    FName LayerTag = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Taxi")
    TArray<FTaxiNodeDef> TaxiNodes;

    UFUNCTION(BlueprintCallable, Category="Taxi")
    void ApplyIsolatedSpawnLayer(AGrayBox_Test* ContextTestPawn);

    UFUNCTION(BlueprintCallable, Category="Taxi")
    void ClearIsolatedLayer();

private:
    UPROPERTY()
    TArray<AActor*> SpawnedIsolatedActors;
};
