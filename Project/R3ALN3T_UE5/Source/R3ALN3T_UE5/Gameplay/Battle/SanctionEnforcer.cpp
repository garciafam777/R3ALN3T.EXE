// SanctionEnforcer.cpp — GAMMA verdict sanction system (Nyx/engine-dev)
#include "SanctionEnforcer.h"
#include "Core/Managers/R3ALSaveGame.h"
#include "AI/Perception/AIPerceptionComponent.h"

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
		if (T == ESanctionType::MARKED)  Boost += 500.f;   // visual tag
		if (T == ESanctionType::WANTED)  Boost += 1500.f;  // bounty hunt
		if (T == ESanctionType::FUGITIVE) Boost += 3000.f; // GAMMA manhunt
	}
	return Boost; // caller adds to AIPerceptionComponent sight radius
}

bool USanctionEnforcer::IsFugitive(AActor* Target) const
{
	if (!Target) return false;
	const TArray<ESanctionType>* S = ActiveSanctions.Find(Target);
	return S && S->Contains(ESanctionType::FUGITIVE);
}

bool USanctionEnforcer::ShouldTransformToEcho(AActor* Target) const
{
	if (!Target) return false;
	const TArray<ESanctionType>* S = ActiveSanctions.Find(Target);
	return S && S->Contains(ESanctionType::ECHOED); // character loss -> AEchoNPC
}

void USanctionEnforcer::PersistTo(UR3ALSaveGame* Save) const
{
	if (!Save) return;
	Save->ActiveSanctions.Reset();
	for (const TPair<AActor*, TArray<ESanctionType>>& Pair : ActiveSanctions)
		Save->ActiveSanctions.Append(Pair.Value);
}
