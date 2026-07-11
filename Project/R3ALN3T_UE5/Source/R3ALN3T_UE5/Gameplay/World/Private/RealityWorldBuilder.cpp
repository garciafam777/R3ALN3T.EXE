#include "../Public/RealityWorldBuilder.h"
#include "../Public/WorldLayerManager.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshActor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"

ARealityWorldBuilder::ARealityWorldBuilder()
{
    PrimaryActorTick.bCanEverTick = false;

    // Default road network - grid pattern for Grid Sectors 01-05
    RoadNetwork = {
        // Main artery N-S
        {FVector(0, -15000, 0), FVector(0, 15000, 0), 500},
        // Main artery E-W
        {FVector(-15000, 0, 0), FVector(15000, 0, 0), 500},
        // Secondary roads
        {FVector(-10000, -10000, 0), FVector(10000, -10000, 0), 300},
        {FVector(-10000, 10000, 0), FVector(10000, 10000, 0), 300},
        {FVector(-10000, -10000, 0), FVector(-10000, 10000, 0), 300},
        {FVector(10000, -10000, 0), FVector(10000, 10000, 0), 300},
        // Diagonal connectors
        {FVector(-5000, -5000, 0), FVector(5000, 5000, 0), 200},
        {FVector(5000, -5000, 0), FVector(-5000, 5000, 0), 200},
    };

    // Building plots around grid
    BuildingPlots = {
        {FVector(-8000, -8000, 0), FVector(600, 400, 250), TEXT("commercial")},
        {FVector(8000, -8000, 0), FVector(700, 500, 300), TEXT("commercial")},
        {FVector(-8000, 8000, 0), FVector(500, 500, 200), TEXT("residential")},
        {FVector(8000, 8000, 0), FVector(600, 600, 350), TEXT("admin")},
        {FVector(-12000, 0, 0), FVector(800, 400, 200), TEXT("residential")},
        {FVector(12000, 0, 0), FVector(400, 800, 250), TEXT("residential")},
        {FVector(0, -12000, 0), FVector(600, 600, 300), TEXT("commercial")},
        {FVector(0, 12000, 0), FVector(700, 500, 280), TEXT("admin")},
        // Outer ring
        {FVector(-14000, -14000, 0), FVector(500, 500, 200), TEXT("residential")},
        {FVector(14000, -14000, 0), FVector(500, 500, 200), TEXT("residential")},
        {FVector(-14000, 14000, 0), FVector(500, 500, 200), TEXT("residential")},
        {FVector(14000, 14000, 0), FVector(600, 600, 250), TEXT("commercial")},
    };

    // Grid sectors - encounter zones
    GridSectors = {
        {TEXT("SECTOR_01"), FVector(-5000, -5000, 0), 3000, 1},
        {TEXT("SECTOR_02"), FVector(5000, -5000, 0), 3000, 2},
        {TEXT("SECTOR_03"), FVector(-5000, 5000, 0), 3000, 2},
        {TEXT("SECTOR_04"), FVector(5000, 5000, 0), 3000, 3},
        {TEXT("SECTOR_05"), FVector(0, 0, 0), 4000, 1},
    };
}

void ARealityWorldBuilder::BeginPlay()
{
    Super::BeginPlay();
    BuildWorld();
}

void ARealityWorldBuilder::BuildWorld()
{
    // Static mesh references should be assigned in the editor or Blueprint.
    // Runtime uses whatever is already set via UPROPERTY(EditAnywhere).
    
    for (const auto& Road : RoadNetwork)
        SpawnRoad(Road);

    for (const auto& Plot : BuildingPlots)
        SpawnBuilding(Plot);

    UE_LOG(LogTemp, Log, TEXT("RealityWorldBuilder: Built %d roads, %d buildings, %d sectors"),
        RoadNetwork.Num(), BuildingPlots.Num(), GridSectors.Num());
}

void ARealityWorldBuilder::ClearWorld()
{
    for (AActor* Actor : SpawnedActors)
    {
        if (Actor && !Actor->IsPendingKillPending())
            Actor->Destroy();
    }
    SpawnedActors.Empty();
}

void ARealityWorldBuilder::SpawnRoad(const FRoadSegment& Segment)
{
    if (!RoadMesh) return;

    FVector Mid = (Segment.Start + Segment.End) * 0.5f;
    FVector Dir = Segment.End - Segment.Start;
    float Length = Dir.Size();
    Dir.Normalize();

    FRotator Rot = Dir.Rotation();
    Rot.Pitch = 0;

    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    AStaticMeshActor* Road = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), FTransform(Rot, Mid), Params);
    if (Road)
    {
        Road->GetStaticMeshComponent()->SetStaticMesh(RoadMesh);
        Road->SetActorScale3D(FVector(Length / 100.0f, Segment.Width / 100.0f, 0.2f));
        if (RoadMaterial)
            Road->GetStaticMeshComponent()->SetMaterial(0, RoadMaterial);
#if WITH_EDITOR
        Road->SetActorLabel(FString::Printf(TEXT("Road_%.0f_%.0f"), Mid.X, Mid.Y));
#endif
        SpawnedActors.Add(Road);
    }
}

void ARealityWorldBuilder::SpawnBuilding(const FBuildingPlot& Plot)
{
    if (!BuildingMesh) return;

    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    AStaticMeshActor* Building = GetWorld()->SpawnActor<AStaticMeshActor>(
        AStaticMeshActor::StaticClass(), FTransform(FRotator::ZeroRotator, Plot.Location + FVector(0, 0, Plot.Extent.Z * 0.5f)), Params);
    if (Building)
    {
        Building->GetStaticMeshComponent()->SetStaticMesh(BuildingMesh);
        Building->SetActorScale3D(Plot.Extent / 100.0f);
        if (BuildingMaterial)
            Building->GetStaticMeshComponent()->SetMaterial(0, BuildingMaterial);
#if WITH_EDITOR
        Building->SetActorLabel(FString::Printf(TEXT("Building_%s_%.0f_%.0f"), *Plot.BuildingType, Plot.Location.X, Plot.Location.Y));
#endif
        SpawnedActors.Add(Building);
    }
}

void ARealityWorldBuilder::RegisterEncounterZones(UWorldLayerManager* Manager)
{
    if (!Manager) return;

    for (const auto& Sector : GridSectors)
    {
        FEncounterZone Zone;
        Zone.ZoneCenter = Sector.Location;
        Zone.ZoneRadius = Sector.Radius;
        Zone.Layer = ER3ALN3TLayer::Reality;
        Zone.MinVirusLevel = Sector.VirusLevel;
        Zone.MaxVirusLevel = Sector.VirusLevel + 2;
        Zone.EncounterRate = 0.03f + (Sector.VirusLevel * 0.01f);
        Manager->AddEncounterZone(Zone);
    }
}
