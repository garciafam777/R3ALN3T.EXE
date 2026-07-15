// BattleGridManager.h
// Revision of the original ISM-based grid manager: now spawns one ABattleStagePanel
// per tile instead of using instanced static mesh + custom data. This trades a small
// amount of draw-call efficiency (32 actors instead of 1 ISM) for the ability to
// independently animate, break, and bevel-light each panel as real 3D geometry —
// worth it at this panel count (32 tiles is nothing for modern hardware), and it's
// what actually gets you the Smash-Bros-stage look instead of a flat board.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../../Core/Types/BattleGridTypes.h"
#include "../../../Core/Types/TrinityMatrixTypes.h"
#include "BattleGridManager.generated.h"

class ABattleStagePanel;

UCLASS()
class R3ALN3T_UE5_API ABattleGridManager : public AActor
{
	GENERATED_BODY()

public:
	ABattleGridManager();

	static constexpr int32 GridCols = 8;
	static constexpr int32 GridRows = 4;
	static constexpr int32 MedianCol = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	float TileSize = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	float TileGap = 8.f; // visible gap between panels, Smash-Battlefield style separation

	UPROPERTY(EditAnywhere, Category = "Grid")
	TSubclassOf<ABattleStagePanel> PanelClass;

	UPROPERTY(VisibleAnywhere)
	TArray<FBattleGridPanel> PanelData; // logical state (occupied/broken/element), separate from the visual actor

	UPROPERTY(VisibleAnywhere)
	TArray<ABattleStagePanel*> PanelActors; // visual actors, indexed identically to PanelData

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid|Colors")
	FLinearColor TierColor; // set from player's Tier/Rank/Element on battle start

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid|Colors")
	FLinearColor LocationColor; // set from current zone/region lore on battle start

	UFUNCTION(BlueprintCallable, Category = "Grid")
	FBattleGridPanel& GetPanelData(const FGridCoord& Coord);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	ABattleStagePanel* GetPanelActor(const FGridCoord& Coord);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	bool IsValidCoord(const FGridCoord& Coord) const;

	UFUNCTION(BlueprintCallable, Category = "Grid")
	bool IsWalkable(const FGridCoord& Coord) const;

	UFUNCTION(BlueprintCallable, Category = "Grid")
	bool CrossesMedian(const FGridCoord& From, const FGridCoord& To) const;

	UFUNCTION(BlueprintCallable, Category = "Grid")
	FVector GridToWorld(const FGridCoord& Coord) const;

	UFUNCTION(BlueprintCallable, Category = "Grid|Colors")
	void RefreshAllPanelColors();

	// Call when a unit moves onto/off of a panel, drives the EdgeGlow highlight pulse
	UFUNCTION(BlueprintCallable, Category = "Grid")
	void SetPanelOccupied(const FGridCoord& Coord, bool bOccupied, FLinearColor OccupantHighlightColor);

	// Encounter seam: place an enemy NetP on the 8x4 board.
	// Gate 1: enemies restricted to columns 4-7 (EnemyColumns, mirrors R3ALN3T_BattleManager).
	// Gate 2: ZETA ceiling clamp on Tier (never Omega) so a bad data feed can't corrupt run state.
	// Returns false (and logs) if the cell is outside the enemy zone or the coord is invalid;
	// on success it sanitizes Tier and marks the panel occupied via SetPanelOccupied.
	UFUNCTION(BlueprintCallable, Category = "Grid|Encounter")
	bool TryPlaceNetPAtCell(int32 Row, int32 Col, FR3ALN3TNetPStatus& NetP, FLinearColor OccupantColor);

	// ZETA ceiling constant (canonical: starter-grade, excludes OMEGA + EPSILON..ALPHA).
	// Mirrors NetPRandomizer::AllowedTiers. Tunable here for the grid's slice.
	static constexpr EGreekTier ZetaCeiling = EGreekTier::Zeta;

protected:
	virtual void BeginPlay() override;
	void SpawnPanels();
};
