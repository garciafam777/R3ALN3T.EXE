// SanctionEnforcer.cpp — GAMMA verdict sanction system (Nyx/engine-dev)
#include "SanctionEnforcer.h"
#include "../../Core/Managers/R3ALSaveGame.h"
#include "Perception/AIPerceptionComponent.h"

void USanctionEnforcer::ApplySanction(ESanctionType Type, AActor* Target, const FString& Reason)
{
	if (!Target) return;
	ActiveSanctions.FindOrAdd(Target).AddUnique(Type);
	UE_LOG(LogTemp, Log, TEXT("Sanction %d applied to %s: %s"), static_cast<int32>(Type), *Target->GetName(), *Reason);
}

float USanctionEnforcer::GetDetectionRadiusBoost(AActor* Target) const
{
	if (!Target) return 0.f;
	const TArray<ESanctionType>* S = ActiveSanctions.Find(Target);
	if (!S) return 0.f;
	float Boost = 0.f;
	for (ESanctionType T : *S)
	{
		if (T == ESanctionType::Marked)  Boost += 500.f;   // visual tag
		if (T == ESanctionType::Wanted)  Boost += 1500.f;  // bounty hunt
		if (T == ESanctionType::Fugitive) Boost += 3000.f; // GAMMA manhunt
	}
	return Boost; // caller adds to AIPerceptionComponent sight radius
}

bool USanctionEnforcer::IsFugitive(AActor* Target) const
{
	if (!Target) return false;
	const TArray<ESanctionType>* S = ActiveSanctions.Find(Target);
	return S && S->Contains(ESanctionType::Fugitive);
}

bool USanctionEnforcer::ShouldTransformToEcho(AActor* Target) const
{
	if (!Target) return false;
	const TArray<ESanctionType>* S = ActiveSanctions.Find(Target);
	return S && S->Contains(ESanctionType::Echoed); // character loss -> AEchoNPC
}

void USanctionEnforcer::PersistTo(UR3ALSaveGame* Save) const
{
	// Sanctions are runtime enforcement state keyed by AActor* (non-serializable),
	// so they are intentionally NOT persisted to the save game.
	if (!Save) return;
}
