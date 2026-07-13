// SanctionEnforcer.h — GAMMA verdict sanction system (Nyx/engine-dev v2, self-contained)
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../Core/Types/TrinityMatrixTypes.h"
#include "SanctionEnforcer.generated.h"

class AActor;
class UR3ALSaveGame;

// The 12 GAMMA-verdict sanctions (persisted to save; AI-perception hooks).
UENUM(BlueprintType)
enum class ESanctionType : uint8
{
    Marked, Wanted, Fugitive, Echoed, Quarantined, Seized,
    Tracked, Suppressed, Corrupted, Banished, Nulled, Recalled
};

UCLASS()
class R3ALN3T_UE5_API USanctionEnforcer : public UObject
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="R3ALN3T|Sanction")
    void ApplySanction(ESanctionType Type, AActor* Target, const FString& Reason);

    // MARKED / WANTED: boost hostile AI detection radius (perception hook).
    UFUNCTION(BlueprintCallable, Category="R3ALN3T|Sanction")
    float GetDetectionRadiusBoost(AActor* Target) const;

    // FUGITIVE: GAMMA NPCs auto-detect + teleport to player on same map.
    UFUNCTION(BlueprintCallable, Category="R3ALN3T|Sanction")
    bool IsFugitive(AActor* Target) const;

    // ECHOED: convert player pawn to AEchoNPC (retained inventory, locked controls).
    UFUNCTION(BlueprintCallable, Category="R3ALN3T|Sanction")
    bool ShouldTransformToEcho(AActor* Target) const;

    UFUNCTION(BlueprintCallable, Category="R3ALN3T|Sanction")
    void PersistTo(UR3ALSaveGame* Save) const;

    // Debug accessor: returns the active sanctions for a target (read-only).
    // Used by the GapF headless harness to verify AddUnique idempotency.
    const TArray<ESanctionType>* GetActiveSanctionsForDebug(AActor* Target) const;

protected:
    // Runtime-only sanction tracking (not serialized; AActor* key is non-reflectable).
    TMap<TObjectPtr<AActor>, TArray<ESanctionType>> ActiveSanctions;
};
