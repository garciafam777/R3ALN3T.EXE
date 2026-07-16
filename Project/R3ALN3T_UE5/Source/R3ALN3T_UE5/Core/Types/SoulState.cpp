// SoulState.cpp
#include "SoulState.h"
#include "UObject/NoExportTypes.h"
#include "../Managers/R3ALSaveGame.h"   // Area-3: persist player soul band to disk

void FSoulState::WriteToSave(UObject* Outer)
{
	UR3ALSaveGame* Save = UR3ALSaveGame::LoadOrCreate(Outer);
	if (!Save)
	{
		return;
	}
	Save->PlayerSoulBand = GetBand();
	UR3ALSaveGame::Save(Outer, Save);
}

ESoulFork ClassifyOutcome(int32 EnemyHPBefore, int32 EnemyHPAfter)
{
	const int32 Dealt = FMath::Max(0, EnemyHPBefore - EnemyHPAfter);
	if (EnemyHPAfter <= 0) return ESoulFork::Purge;       // enemy destroyed
	if (Dealt > 0)        return ESoulFork::Corrupt;      // damaged but survived
	return ESoulFork::Spare;                              // no damage dealt
}

FString GetForkName(ESoulFork Fork)
{
	const UEnum* E = StaticEnum<ESoulFork>();
	return E ? E->GetNameStringByValue(static_cast<int64>(Fork)) : FString(TEXT("?"));
}

float ApplyDamageFork(FSoulState& Soul, int32 EnemyHPBefore, int32 EnemyHPAfter, ESoulFork Fork)
{
	const int32 Dealt = FMath::Max(0, EnemyHPBefore - EnemyHPAfter);
	const bool bDied = EnemyHPAfter <= 0;
	const bool bSurvived = !bDied;
	const bool bTookDamage = Dealt > 0;

	float Shift = 0.f;
	switch (Fork)
	{
	case ESoulFork::Spare:
		Shift = bSurvived ? 4.f : -6.f;   // mercy held vs. collateral death
		break;
	case ESoulFork::Purge:
		Shift = bDied ? -2.f : 3.f;       // cleansed vs. unfinished purge lingers
		break;
	case ESoulFork::Corrupt:
		Shift = bTookDamage ? 7.f : 2.f;  // fed corruption vs. wasted
		break;
	default:
		// No intent: shift by the bare outcome so the system still moves.
		Shift = (Fork == ESoulFork::Purge) ? -6.f : (bTookDamage ? 4.f : 0.f);
		break;
	}

	const float Before = Soul.Soul;
	Soul.Soul = FMath::Clamp(Before + Shift, 0.f, 100.f);
	return Soul.Soul - Before;
}
