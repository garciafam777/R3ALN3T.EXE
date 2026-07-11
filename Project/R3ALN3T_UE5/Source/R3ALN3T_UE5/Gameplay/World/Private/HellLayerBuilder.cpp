#include "../Public/HellLayerBuilder.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshActor.h"
#include "Components/StaticMeshComponent.h"

AHellLayerBuilder::AHellLayerBuilder()
{
    PrimaryActorTick.bCanEverTick = false;

    LavaRiverPoints = {
        FVector(-5000, -2000, -100000), FVector(2000, 3000, -100000),
        FVector(8000, -1000, -100000), FVector(-3000, -5000, -100000),
    };

    ObsidianSpireLocations = {
        FVector(-6000, -4000, -100000), FVector(6000, 3000, -100000),
        FVector(-2000, 5000, -100000), FVector(4000, -5000, -100000),
        FVector(0, 0, -100000),
    };

    HellEncounterZones = {
        {FVector(-3000, -3000, -100000), 2500, ER3ALN3TLayer::Hell, 4, 6, 0.06f},
        {FVector(3000, 3000, -100000), 2500, ER3ALN3TLayer::Hell, 5, 7, 0.07f},
        {FVector(0, 0, -100000), 4000, ER3ALN3TLayer::Hell, 3, 5, 0.05f},
    };
}

void AHellLayerBuilder::BeginPlay()
{
    Super::BeginPlay();
    BuildHellscape();
}

void AHellLayerBuilder::BuildHellscape()
{
    for (int32 i = 0; i < LavaRiverPoints.Num(); i += 2)
    {
        if (i + 1 < LavaRiverPoints.Num())
            SpawnLavaRiver(LavaRiverPoints[i], LavaRiverPoints[i+1]);
    }
    for (const auto& Spire : ObsidianSpireLocations)
        SpawnObsidianSpire(Spire);

    UE_LOG(LogTemp, Log, TEXT("HellLayerBuilder: Hellscape built with %d spires"), ObsidianSpireLocations.Num());
}

void AHellLayerBuilder::SpawnLavaRiver(FVector Start, FVector End)
{
    // Placeholder: spawn scaled cube as lava river segment
    if (!HasAnyFlags(RF_ClassDefaultObject))
    {
        UStaticMesh* CubeMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cube.Cube"));
        if (CubeMesh)
        {
            FVector Mid = (Start + End) * 0.5f;
            float Length = FVector::Dist(Start, End);
            FActorSpawnParameters P;
            P.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
            AStaticMeshActor* River = GetWorld()->SpawnActor<AStaticMeshActor>(
                AStaticMeshActor::StaticClass(), FTransform(FRotator::ZeroRotator, Mid), P);
            if (River)
            {
                River->GetStaticMeshComponent()->SetStaticMesh(CubeMesh);
                River->SetActorScale3D(FVector(Length / 100, 400 / 100, 0.1f));
#if WITH_EDITOR
                River->SetActorLabel(TEXT("LavaRiver"));
#endif
            }
        }
    }
}

void AHellLayerBuilder::SpawnObsidianSpire(FVector Location)
{
    UStaticMesh* CubeMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cone.Cone"));
    if (CubeMesh)
    {
        FActorSpawnParameters P;
        P.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        AStaticMeshActor* Spire = GetWorld()->SpawnActor<AStaticMeshActor>(
            AStaticMeshActor::StaticClass(), FTransform(FRotator::ZeroRotator, Location + FVector(0,0,500)), P);
        if (Spire)
        {
            Spire->GetStaticMeshComponent()->SetStaticMesh(CubeMesh);
            Spire->SetActorScale3D(FVector(3, 3, 10));
#if WITH_EDITOR
            Spire->SetActorLabel(TEXT("ObsidianSpire"));
#endif
        }
    }
}

void AHellLayerBuilder::RegisterZones(UWorldLayerManager* Manager)
{
    if (!Manager) return;
    for (const auto& Zone : HellEncounterZones)
        Manager->AddEncounterZone(Zone);
}
