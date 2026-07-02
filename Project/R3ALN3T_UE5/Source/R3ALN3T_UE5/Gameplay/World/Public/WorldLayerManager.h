// WorldLayerManager.h
// Manages the 6-layer dimensional world system with streaming, spawning, and zone management.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../R3ALN3T_WorldStructures.h"
#include "WorldLayerManager.generated.h"

class APlayerController;

USTRUCT(BlueprintType)
struct FWorldLayerInfo
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    ER3ALN3TLayer Layer = ER3ALN3TLayer::Reality;

    UPROPERTY(BlueprintReadOnly)
    FString DisplayName;

    UPROPERTY(BlueprintReadOnly)
    FName LevelName;

    UPROPERTY(BlueprintReadOnly)
    FVector SpawnOffset = FVector::ZeroVector;

    UPROPERTY(BlueprintReadOnly)
    int32 Priority = 0;
};

USTRUCT(BlueprintType)
struct FEncounterZone
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector ZoneCenter;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ZoneRadius = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ER3ALN3TLayer Layer = ER3ALN3TLayer::Reality;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MinVirusLevel = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxVirusLevel = 3;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EncounterRate = 0.05f; // 5% chance per step
};

UCLASS(BlueprintType)
class R3ALN3T_UE5_API UWorldLayerManager : public UObject
{
    GENERATED_BODY()

public:
    void Init();

    UFUNCTION(BlueprintCallable, Category = "World")
    bool TeleportToLayer(APlayerController* Player, ER3ALN3TLayer TargetLayer);

    UFUNCTION(BlueprintCallable, Category = "World")
    ER3ALN3TLayer GetCurrentLayer() const { return CurrentLayer; }

    UFUNCTION(BlueprintCallable, Category = "World")
    const TArray<FWorldLayerInfo>& GetLayerInfos() const { return LayerInfos; }

    UFUNCTION(BlueprintCallable, Category = "World")
    bool IsInEncounterZone(FVector Location, FEncounterZone& OutZone) const;

    UFUNCTION(BlueprintCallable, Category = "World")
    void AddEncounterZone(const FEncounterZone& Zone);

    UFUNCTION(BlueprintCallable, Category = "World")
    TArray<FEncounterZone> GetZonesForLayer(ER3ALN3TLayer Layer) const;

    UFUNCTION(BlueprintCallable, Category = "World")
    float GetEncounterChanceAt(FVector Location) const;

private:
    ER3ALN3TLayer CurrentLayer = ER3ALN3TLayer::Reality;
    TArray<FWorldLayerInfo> LayerInfos;
    TArray<FEncounterZone> EncounterZones;

    FString GetLayerName(ER3ALN3TLayer Layer) const;
    FName GetLayerLevelName(ER3ALN3TLayer Layer) const;
    FVector GetLayerSpawnOffset(ER3ALN3TLayer Layer) const;
};
