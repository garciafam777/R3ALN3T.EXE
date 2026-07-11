// SanctionEnforcer.h — GAMMA verdict sanction system (Nyx/engine-dev, compile-ready)
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Core/Types/SoulBattleTypes.h"
#include "SanctionEnforcer.generated.h"

class AActor;
class UR3ALSaveGame;

// Applies the 12 sanction types; persists to USaveGame; integrates with AI perception.
UCLASS()
class R3ALN3T_UE5_API USanctionEnforcer : public UObject
{
	GENERATED_BODY()
public:
	// Apply a sanction to Target. Reason is logged + stored. Persists via SaveGame.
	UFUNCTION(BlueprintCallable, Category = "OMEGA|Sanction")
	void ApplySanction(ESanctionType Type, AActor* Target, const FString& Reason);

	// MARKED / WANTED: boost hostile AI detection radius (perception hook).
	UFUNCTION(BlueprintCallable, Category = "OMEGA|Sanction")
	float GetDetectionRadiusBoost(AActor* Target) const;

	// FUGITIVE: GAMMA NPCs auto-detect + teleport to player on same map.
	UFUNCTION(BlueprintCallable, Category = "OMEGA|Sanction")
	bool IsFugitive(AActor* Target) const;

	// ECHOED: convert player pawn to AEchoNPC (retained inventory, locked controls).
	UFUNCTION(BlueprintCallable, Category = "OMEGA|Sanction")
	bool ShouldTransformToEcho(AActor* Target) const;

	// Persist active sanctions into the save object.
	UFUNCTION(BlueprintCallable, Category = "OMEGA|Sanction")
	void PersistTo(UR3ALSaveGame* Save) const;

protected:
	UPROPERTY() TMap<AActor*, TArray<ESanctionType>> ActiveSanctions;
};
