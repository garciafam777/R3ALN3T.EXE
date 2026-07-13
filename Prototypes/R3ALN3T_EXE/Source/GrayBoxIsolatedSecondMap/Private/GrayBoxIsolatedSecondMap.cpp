// GrayBoxIsolatedSecondMap.cpp
// Second-zone gray-box builder. Reads from frozen local manifest only.
#include "GrayBoxIsolatedSecondMap.h"
#include "Kismet/KismetMathUtilities.h"
#include "Engine/World.h"
#include "ProceduralMeshComponent.h"

AGrayBoxIsolatedSecondMap::AGrayBoxIsolatedSecondMap()
{
    PrimaryActorTick.bCanEverTick = false;
    RegionID = FName("TaxiKingdomIsolation");
    LayerTag = FName("IsolationLayer");
}

void AGrayBoxIsolatedSecondMap::ApplyIsolatedSpawnLayer(AGrayBox_Test* ContextTestPawn)
{
    ClearIsolatedLayer();
    for (const FTaxiNodeDef& Node : TaxiNodes)
    {
        FVector Loc = Node.WorldLocation;
        AStaticMeshActor* TaxiMesh = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), Loc, FRotator::ZeroRotator);
        if (TaxiMesh)
        {
            SpawnedIsolatedActors.Add(TaxiMesh);
            TaxiMesh->SetActorLabel(FString::Printf(TEXT("Taxi_%s"), *Node.NodeID.ToString()));
        }
    }
}

void AGrayBoxIsolatedSecondMap::ClearIsolatedLayer()
{
    for (AActor* Actor : SpawnedIsolatedActors)
    {
        if (IsValid(Actor))
        {
            Actor->Destroy();
        }
    }
    SpawnedIsolatedActors.Empty();
}
