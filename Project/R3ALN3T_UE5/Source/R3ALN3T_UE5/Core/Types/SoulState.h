// SoulState.h
// Gap C (first pass): standalone Soul State component.
// A 0-100 "soul" value plus 7 aura bands (canon: Radiant -> Corrupted, isomorphic to
// Heaven's 7 layers / Hell's 7 stages, Seam = Echo Abyss L1<->S1). The component knows
// nothing about chips or battle — it just accepts a "fork" outcome and shifts itself.
//
// The single hook into gameplay lives in R3ALN3T_BattleManager::PlayChip (see .cpp), which
// calls ApplyDamageFork after chip damage resolves. Chips carry an optional ESoulFork tag
// (FChipDef::SoulFork) so a chip's nature biases the shift; the console test can force any
// fork to exercise all three outcomes on one PIE run.
#pragma once

#include "CoreMinimal.h"
#include "SoulState.generated.h"

// The player's soul disposition expressed through an action. This is the "spare / purge /
// corrupt fork" — the intent carried by a chip or chosen at play.
UENUM(BlueprintType)
enum class ESoulFork : uint8
{
	None   UMETA(DisplayName = "None"),
	Spare  UMETA(DisplayName = "Spare"),    // mercy: leave the node intact
	Purge  UMETA(DisplayName = "Purge"),    // cleanse: erase the bugmatter
	Corrupt UMETA(DisplayName = "Corrupt")  // feed: worsen the compression
};

// The 7 aura bands a 0-100 soul value maps onto.
UENUM(BlueprintType)
enum class ESoulAuraBand : uint8
{
	Radiant,    // 0-13
	Serene,     // 14-27
	Settled,    // 28-41
	Cracked,    // 42-55
	Fractured,  // 56-69
	Twisted,    // 70-83
	Corrupted   // 84-100
};

USTRUCT(BlueprintType)
struct R3ALN3T_UE5_API FSoulState
{
	GENERATED_BODY()

	// 0 = fully Radiant, 100 = fully Corrupted. Starts mid-band ("Cracked").
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soul")
	float Soul = 50.f;

	// Maps the current Soul value onto a named aura band.
	ESoulAuraBand GetBand() const
	{
		if (Soul <= 13.f) return ESoulAuraBand::Radiant;
		if (Soul <= 27.f) return ESoulAuraBand::Serene;
		if (Soul <= 41.f) return ESoulAuraBand::Settled;
		if (Soul <= 55.f) return ESoulAuraBand::Cracked;
		if (Soul <= 69.f) return ESoulAuraBand::Fractured;
		if (Soul <= 83.f) return ESoulAuraBand::Twisted;
		return ESoulAuraBand::Corrupted;
	}

	FString GetBandName() const
	{
		const UEnum* E = StaticEnum<ESoulAuraBand>();
		return E ? E->GetNameStringByValue(static_cast<int64>(GetBand())) : FString(TEXT("?"));
	}

	// Area-3 fix: persist this soul's current band into the on-disk UR3ALSaveGame so the
	// player's soul state survives a restart. Loads (or creates) the save, writes PlayerSoulBand,
	// then flushes. No-op if the save subsystem is unavailable.
	void WriteToSave(UObject* Outer);
};

// Soul shift rule (Gap C v1):
//   intent (Fork) is the player's soul disposition carried by the chip / chosen at play.
//   combat outcome modulates it:
//     Spare  : +4 if enemy survived (mercy held),  -2 if enemy died anyway
//     Purge  : -6 if enemy died (cleansed),        +3 if survived (unfinished purge)
//     Corrupt: +7 if enemy took damage,            +2 if 0 damage (wasted)
//   Soul = clamp(Soul + shift, 0, 100); band recomputed.
// Returns the shift applied (for logging / tests).
R3ALN3T_UE5_API float ApplyDamageFork(
	FSoulState& Soul,
	int32 EnemyHPBefore,
	int32 EnemyHPAfter,
	ESoulFork Fork);

// Pure classification of a chip's combat result into a fork outcome (ignores intent).
R3ALN3T_UE5_API ESoulFork ClassifyOutcome(int32 EnemyHPBefore, int32 EnemyHPAfter);

// String name for a fork (for logs / console).
R3ALN3T_UE5_API FString GetForkName(ESoulFork Fork);
