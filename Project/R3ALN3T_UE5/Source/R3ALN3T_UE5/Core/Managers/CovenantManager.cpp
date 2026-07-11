// CovenantManager.cpp — OMEGA Covenant Pact system (Nyx/engine-dev)
#include "CovenantManager.h"
#include "Engine/GameInstance.h"

void UCovenantManager::AlignWithOMEGA(const FString& OMEGAId)
{
	CovenantStates.FindOrAdd(OMEGAId) = ECovenantState::ALIGNED;
}

void UCovenantManager::DeclareHostility(const FString& OMEGAId)
{
	CovenantStates.FindOrAdd(OMEGAId) = ECovenantState::HOSTILE;
}

bool UCovenantManager::AttemptUsurpation(const FString& OMEGAId, bool bDefeated, int32 GammaVerdicts)
{
	ECovenantState& State = CovenantStates.FindOrAdd(OMEGAId);
	// Preconditions: defeated in combat, >= EXILED tier, >= 3 GAMMA verdicts in player's favor.
	const bool bEligible = bDefeated
		&& (static_cast<uint8>(PlayerSupremacy) >= static_cast<uint8>(ESupremacyTier::EXILED))
		&& (GammaVerdicts >= 3);

	if (bEligible)
	{
		// Success: player becomes the new ELEMENTAL OMEGA for this OMEGA's domain element.
		PlayerSupremacy = ESupremacyTier::ELEMENTAL;
		// Domain = the usurped OMEGA's claimed element (resolved by caller via SetClaimedDomain).
		State = ECovenantState::USURPED; // player now holds the Throne
		return true;
	}

	// Failure: ECHOED — player becomes Echo NPC (character loss per lore).
	State = ECovenantState::USURPED; // flagged; caller transforms pawn to AEchoNPC
	PlayerSupremacy = ESupremacyTier::NONE;
	return false;
}

ECovenantState UCovenantManager::GetCovenantState(const FString& OMEGAId) const
{
	const ECovenantState* Found = CovenantStates.Find(OMEGAId);
	return Found ? *Found : ECovenantState::DORMANT; // default DORMANT (spec: dormant until spawned/aligned)
}
