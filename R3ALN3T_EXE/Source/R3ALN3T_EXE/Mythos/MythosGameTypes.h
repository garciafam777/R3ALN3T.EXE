// Core runtime types for the playable R3ALN3T.EXE mythos prototype.
#pragma once

#include "CoreMinimal.h"
#include "MythosGameTypes.generated.h"

UENUM(BlueprintType)
enum class EMythosFaction : uint8
{
	CelestialOrder,
	AegisConcord,
	N3TDominion,
	UndernetSyndicate,
	AbyssalCovenant,
	FreeGridCollective
};

UENUM(BlueprintType)
enum class EMythosCareer : uint8
{
	Miner,
	Electrician,
	Security,
	Medical,
	Broker,
	Trucker
};

UENUM(BlueprintType)
enum class EMythosElement : uint8
{
	Volt,
	Aqua,
	Terra,
	Shade,
	Flare,
	Signal
};

UENUM(BlueprintType)
enum class EMythosScreen : uint8
{
	Start,
	CareerSelect,
	ElementSelect,
	Work,
	StoryChoice,
	Battle,
	Ending,
	PostGame
};

UENUM(BlueprintType)
enum class EMythosBattleAction : uint8
{
	CrossStrike,
	GuardWall,
	DecodeHack,
	PurifyBurst
};

USTRUCT(BlueprintType)
struct FMythosCareerData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	EMythosCareer Career = EMythosCareer::Miner;

	UPROPERTY(BlueprintReadOnly)
	FString Name;

	UPROPERTY(BlueprintReadOnly)
	FString WorkSite;

	UPROPERTY(BlueprintReadOnly)
	FString Lie;

	UPROPERTY(BlueprintReadOnly)
	int32 MaxHP = 30;

	UPROPERTY(BlueprintReadOnly)
	int32 Attack = 6;

	UPROPERTY(BlueprintReadOnly)
	int32 Tech = 2;

	UPROPERTY(BlueprintReadOnly)
	int32 Shield = 1;

	UPROPERTY(BlueprintReadOnly)
	EMythosFaction Lean = EMythosFaction::FreeGridCollective;
};

USTRUCT(BlueprintType)
struct FMythosChoiceData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString Label;

	UPROPERTY(BlueprintReadOnly)
	FString Description;

	UPROPERTY(BlueprintReadOnly)
	EMythosFaction Faction = EMythosFaction::FreeGridCollective;

	UPROPERTY(BlueprintReadOnly)
	int32 ZDelta = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 CorruptionDelta = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 BondDelta = 0;

	UPROPERTY(BlueprintReadOnly)
	FString ItemReward;
};

USTRUCT(BlueprintType)
struct FMythosStoryNode
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString Title;

	UPROPERTY(BlueprintReadOnly)
	FString Body;

	UPROPERTY(BlueprintReadOnly)
	FString Terminal;

	UPROPERTY(BlueprintReadOnly)
	TArray<FMythosChoiceData> Choices;
};

USTRUCT(BlueprintType)
struct FMythosRunState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString OperatorName = TEXT("MCADMIN?");

	UPROPERTY(BlueprintReadOnly)
	EMythosCareer Career = EMythosCareer::Miner;

	UPROPERTY(BlueprintReadOnly)
	EMythosElement Element = EMythosElement::Volt;

	UPROPERTY(BlueprintReadOnly)
	EMythosScreen Screen = EMythosScreen::Start;

	UPROPERTY(BlueprintReadOnly)
	int32 Day = 1;

	UPROPERTY(BlueprintReadOnly)
	int32 ActIndex = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 Rank = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 HP = 30;

	UPROPERTY(BlueprintReadOnly)
	int32 MaxHP = 30;

	UPROPERTY(BlueprintReadOnly)
	int32 Attack = 6;

	UPROPERTY(BlueprintReadOnly)
	int32 Tech = 2;

	UPROPERTY(BlueprintReadOnly)
	int32 Shield = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 Z = 500;

	UPROPERTY(BlueprintReadOnly)
	int32 Corruption = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 NetPBond = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 Celestial = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 Aegis = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 Dominion = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 Undernet = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 Abyssal = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 FreeGrid = 0;

	UPROPERTY(BlueprintReadOnly)
	FString Objective;

	UPROPERTY(BlueprintReadOnly)
	FString EndingName;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> Inventory;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> Log;
};
