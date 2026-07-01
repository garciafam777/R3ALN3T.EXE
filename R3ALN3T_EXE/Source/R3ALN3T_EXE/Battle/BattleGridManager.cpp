// BattleGridManager.cpp
#include "BattleGridManager.h"
#include "BattleStagePanel.h"
#include "BattleGridTypes.h"

ABattleGridManager::ABattleGridManager()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

void ABattleGridManager::BeginPlay()
{
	Super::BeginPlay();
	SpawnPanels();
	RefreshAllPanelColors();
}

void ABattleGridManager::SpawnPanels()
{
	if (!PanelClass)
	{
		UE_LOG(LogTemp, Error, TEXT("ABattleGridManager: PanelClass not set, no panels spawned"));
		return;
	}

	PanelData.SetNum(GridCols * GridRows);
	PanelActors.SetNum(GridCols * GridRows);

	for (int32 Row = 0; Row < GridRows; ++Row)
	{
		for (int32 Col = 0; Col < GridCols; ++Col)
		{
			const int32 Index = Row * GridCols + Col;

			FBattleGridPanel Data;
			Data.Coord = FGridCoord(Col, Row);
			PanelData[Index] = Data;

			const FVector SpawnLoc = GridToWorld(Data.Coord);
			FActorSpawnParameters Params;
			Params.Owner = this;

			ABattleStagePanel* Panel = GetWorld()->SpawnActor<ABattleStagePanel>(PanelClass, FTransform(SpawnLoc), Params);
			if (Panel)
			{
				Panel->Coord = Data.Coord;
				// Slightly scale panel mesh down vs TileSize so TileGap reads as a visible seam
				// between panels — do the actual scale-to-fit math against your specific mesh's
				// bounds in BP or here once you've picked the chamfered-box asset.
			}
			PanelActors[Index] = Panel;
		}
	}
}

FBattleGridPanel& ABattleGridManager::GetPanelData(const FGridCoord& Coord)
{
	check(IsValidCoord(Coord));
	return PanelData[Coord.Row * GridCols + Coord.Col];
}

ABattleStagePanel* ABattleGridManager::GetPanelActor(const FGridCoord& Coord)
{
	if (!IsValidCoord(Coord)) return nullptr;
	return PanelActors[Coord.Row * GridCols + Coord.Col];
}

bool ABattleGridManager::IsValidCoord(const FGridCoord& Coord) const
{
	return Coord.Col >= 0 && Coord.Col < GridCols && Coord.Row >= 0 && Coord.Row < GridRows;
}

bool ABattleGridManager::IsWalkable(const FGridCoord& Coord) const
{
	if (!IsValidCoord(Coord)) return false;
	const FBattleGridPanel& P = PanelData[Coord.Row * GridCols + Coord.Col];
	return !P.bOccupied && !P.bBroken;
}

bool ABattleGridManager::CrossesMedian(const FGridCoord& From, const FGridCoord& To) const
{
	return From.GetSide() != To.GetSide();
}

FVector ABattleGridManager::GridToWorld(const FGridCoord& Coord) const
{
	const float Step = TileSize + TileGap;
	const float X = (Coord.Col - (GridCols / 2.f) + 0.5f) * Step;
	const float Y = (Coord.Row - (GridRows / 2.f) + 0.5f) * Step;
	return GetActorLocation() + FVector(X, Y, 0.f);
}

void ABattleGridManager::RefreshAllPanelColors()
{
	for (int32 i = 0; i < PanelData.Num(); ++i)
	{
		const FBattleGridPanel& Data = PanelData[i];
		ABattleStagePanel* Panel = PanelActors[i];
		if (!Panel) continue;

		FLinearColor Color = (Data.Coord.GetSide() == EGridSide::Player) ? TierColor : LocationColor;
		if (Data.TintOverride.A > 0.f)
		{
			Color = Data.TintOverride; // elemental/hazard panel override wins
		}
		Panel->SetBaseColor(Color);
	}
}

void ABattleGridManager::SetPanelOccupied(const FGridCoord& Coord, bool bOccupied, FLinearColor OccupantHighlightColor)
{
	if (!IsValidCoord(Coord)) return;
	GetPanelData(Coord).bOccupied = bOccupied;
	if (ABattleStagePanel* Panel = GetPanelActor(Coord))
	{
		Panel->SetHighlighted(bOccupied, OccupantHighlightColor);
	}
}
