// BattleGridTypes.h
// Core data types for the 8x4 split battlefield (4x4 player side + 4x4 enemy
// side, median is a logical column boundary, not a physical wall).
#pragma once
#include "CoreMinimal.h"
#include "BattleGridTypes.generated.h"

UENUM(BlueprintType)
enum class EGridSide : uint8
{
	Player,
	Enemy
};

UENUM(BlueprintType)
enum class EBattleElementType : uint8
{
	None, Fire, Aqua, Elec, Wood, Wind, Holy, Void
};

USTRUCT(BlueprintType)
struct FGridCoord
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Col = 0; // 0-7 across the full 8x4 board (0-3 player, 4-7 enemy)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Row = 0; // 0-3

	FGridCoord() {}
	FGridCoord(int32 InCol, int32 InRow) : Col(InCol), Row(InRow) {}

	bool operator==(const FGridCoord& Other) const
	{
		return Col == Other.Col && Row == Other.Row;
	}

	EGridSide GetSide() const
	{
		return Col < 4 ? EGridSide::Player : EGridSide::Enemy;
	}
};

USTRUCT(BlueprintType)
struct FBattleGridPanel
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGridCoord Coord;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bOccupied = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBroken = false; // cracked/blown-up panel, can't stand on it

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBattleElementType PanelElement = EBattleElementType::None; // panel-based elemental buffs

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor TintOverride = FLinearColor(0, 0, 0, 0); // alpha 0 = use side default color
};
