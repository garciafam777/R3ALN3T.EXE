// FTableRowBase structs for data-driven narrative — stored in UDataTable assets.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "../Mythos/MythosGameTypes.h"
#include "DataTypes.generated.h"

USTRUCT(BlueprintType)
struct FNarrativeStoryRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narrative")
	FName NodeID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narrative")
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narrative")
	FText Body;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narrative")
	FText TerminalText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narrative")
	int32 ActIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narrative")
	int32 MinDay = 0;
};

USTRUCT(BlueprintType)
struct FNarrativeChoiceRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narrative")
	FName NodeID; // FK to FNarrativeStoryRow

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narrative")
	int32 ChoiceIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narrative")
	FText Label;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narrative")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narrative")
	EMythosFaction Faction = EMythosFaction::FreeGridCollective;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narrative")
	int32 ZDelta = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narrative")
	int32 CorruptionDelta = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narrative")
	int32 BondDelta = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narrative")
	FName ItemReward;
};

USTRUCT(BlueprintType)
struct FEnemyRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	FName EnemyID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	FText IntroText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int32 HP = 24;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int32 Attack = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int32 MinAct = 0;
};
