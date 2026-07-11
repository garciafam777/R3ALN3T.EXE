// CovenantManager.h — OMEGA Covenant Pact system (Nyx/engine-dev, compile-ready)
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Core/Types/SoulBattleTypes.h"
#include "CovenantManager.generated.h"

// Singleton component owning OMEGA covenant relationships. Attached to UR3ALN3TGameInstance.
UCLASS()
class R3ALN3T_UE5_API UCovenantManager : public UObject
{
	GENERATED_BODY()
public:
	// Align with an OMEGA: gain its elemental blessing (state -> ALIGNED).
	UFUNCTION(BlueprintCallable, Category = "OMEGA|Covenant")
	void AlignWithOMEGA(const FString& OMEGAId);

	// Declare hostility: state -> HOSTILE.
	UFUNCTION(BlueprintCallable, Category = "OMEGA|Covenant")
	void DeclareHostility(const FString& OMEGAId);

	// Attempt usurpation. Requires: defeat OMEGA in combat (bDefeated),
	// SupremacyTier >= EXILED, and >=3 favorable GAMMA verdicts (GammaVerdicts).
	// On success: player becomes ELEMENTAL OMEGA for that element, same-element NPCs ally.
	// On failure: player -> ECHOED (ECovenantState::USURPED, character loss per lore).
	UFUNCTION(BlueprintCallable, Category = "OMEGA|Covenant")
	bool AttemptUsurpation(const FString& OMEGAId, bool bDefeated, int32 GammaVerdicts);

	// Query current covenant state for an OMEGA.
	UFUNCTION(BlueprintCallable, Category = "OMEGA|Covenant")
	ECovenantState GetCovenantState(const FString& OMEGAId) const;

protected:
	// OMEGA id -> covenant state. Scripted-spawn OMEGAs default DORMANT.
	UPROPERTY() TMap<FString, ECovenantState> CovenantStates;
	// Player's acquired supremacy tier (set on successful usurp).
	UPROPERTY() ESupremacyTier PlayerSupremacy = ESupremacyTier::NONE;
	// Element the player claimed via usurp (valid when PlayerSupremacy == ELEMENTAL).
	UPROPERTY() EBattleElementType ClaimedDomain = EBattleElementType::None;
};
