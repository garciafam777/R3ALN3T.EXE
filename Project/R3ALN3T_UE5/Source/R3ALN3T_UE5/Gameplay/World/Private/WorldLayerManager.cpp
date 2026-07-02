#include "../Public/WorldLayerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void UWorldLayerManager::Init()
{
    LayerInfos.Empty();

    auto AddLayer = [&](ER3ALN3TLayer L, const FString& Name, FName Level, FVector Offset, int32 Pri)
    {
        FWorldLayerInfo Info;
        Info.Layer = L;
        Info.DisplayName = Name;
        Info.LevelName = Level;
        Info.SpawnOffset = Offset;
        Info.Priority = Pri;
        LayerInfos.Add(Info);
    };

    AddLayer(ER3ALN3TLayer::Heaven,        TEXT("Heaven"),        TEXT("L_Heaven"),        FVector(0,0,100000),  6);
    AddLayer(ER3ALN3TLayer::OuterSpace,    TEXT("Outer Space"),   TEXT("L_OuterSpace"),    FVector(0,0,50000),   5);
    AddLayer(ER3ALN3TLayer::LunaMars,      TEXT("Luna / Mars"),   TEXT("L_LunaMars"),      FVector(0,0,20000),   4);
    AddLayer(ER3ALN3TLayer::Reality,       TEXT("R3AL World"),    TEXT("L_Reality"),       FVector(0,0,0),       3);
    AddLayer(ER3ALN3TLayer::Cyberspace,    TEXT("Cyberspace"),    TEXT("L_Cyberspace"),    FVector(0,0,0),       2);
    AddLayer(ER3ALN3TLayer::Hell,          TEXT("Hell"),          TEXT("L_Hell"),          FVector(0,0,-100000), 1);
}

FString UWorldLayerManager::GetLayerName(ER3ALN3TLayer Layer) const
{
    for (const auto& Info : LayerInfos)
        if (Info.Layer == Layer) return Info.DisplayName;
    return TEXT("Unknown");
}

FName UWorldLayerManager::GetLayerLevelName(ER3ALN3TLayer Layer) const
{
    for (const auto& Info : LayerInfos)
        if (Info.Layer == Layer) return Info.LevelName;
    return NAME_None;
}

FVector UWorldLayerManager::GetLayerSpawnOffset(ER3ALN3TLayer Layer) const
{
    for (const auto& Info : LayerInfos)
        if (Info.Layer == Layer) return Info.SpawnOffset;
    return FVector::ZeroVector;
}

bool UWorldLayerManager::TeleportToLayer(APlayerController* Player, ER3ALN3TLayer TargetLayer)
{
    if (!Player || !Player->GetWorld()) return false;

    FName LevelName = GetLayerLevelName(TargetLayer);
    if (LevelName == NAME_None) return false;

    CurrentLayer = TargetLayer;

    // Stream the target level
    FLatentActionInfo LatentInfo;
    UGameplayStatics::LoadStreamLevel(Player->GetWorld(), LevelName, true, true, LatentInfo);

    // Move player to spawn offset
    FVector Offset = GetLayerSpawnOffset(TargetLayer);
    Player->GetPawn()->SetActorLocation(Offset);

    UE_LOG(LogTemp, Log, TEXT("Teleported to %s at offset %s"), *GetLayerName(TargetLayer), *Offset.ToString());
    return true;
}

bool UWorldLayerManager::IsInEncounterZone(FVector Location, FEncounterZone& OutZone) const
{
    for (const auto& Zone : EncounterZones)
    {
        if (Zone.Layer != CurrentLayer) continue;
        if (FVector::Distance(Location, Zone.ZoneCenter) <= Zone.ZoneRadius)
        {
            OutZone = Zone;
            return true;
        }
    }
    return false;
}

void UWorldLayerManager::AddEncounterZone(const FEncounterZone& Zone)
{
    EncounterZones.Add(Zone);
}

TArray<FEncounterZone> UWorldLayerManager::GetZonesForLayer(ER3ALN3TLayer Layer) const
{
    TArray<FEncounterZone> Result;
    for (const auto& Z : EncounterZones)
        if (Z.Layer == Layer) Result.Add(Z);
    return Result;
}

float UWorldLayerManager::GetEncounterChanceAt(FVector Location) const
{
    FEncounterZone Dummy;
    if (IsInEncounterZone(Location, Dummy))
        return Dummy.EncounterRate;
    return 0.0f;
}
