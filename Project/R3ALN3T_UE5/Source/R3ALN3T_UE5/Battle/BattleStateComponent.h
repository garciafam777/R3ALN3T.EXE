// BattleStateComponent.h
// The conductor for one combatant's battle-loop: fills the Custom Gauge over
// GaugeFillDuration seconds in real time. When full, sets bGaugeReady = true
// but does NOT auto-open anything — the owning Pawn/Controller calls
// TryOpenChipSelect() itself, bound to L1/R1 (or keyboard equivalent) input.
// Movement is locked for THIS unit only while its own select menu is open;
// it does not freeze the opponent (matches "both sides can be mid-action independently").
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BattleChipTypes.h"
#include "BattleGridTypes.h"
#include "BattleStateComponent.generated.h"

class UChipFolderComponent;
class UGridMoverComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGaugeReady);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChipSelectOpened);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChipSelectLocked, FChipInstance, LockedChip);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChipSelectCancelled);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class R3ALN3T_UE5_API UBattleStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBattleStateComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gauge")
	float GaugeFillDuration = 20.f; // seconds to fill 0 -> 100%

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gauge")
	float GaugeAlpha = 0.f; // 0..1, drive your HUD bar fill width directly from this

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gauge")
	bool bGaugeReady = false; // true once full; stays true until select is opened+resolved

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gauge")
	bool bSelectMenuOpen = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gauge")
	UChipFolderComponent* FolderComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gauge")
	UGridMoverComponent* MoverComponent; // locked while bSelectMenuOpen == true for THIS unit

	UPROPERTY(BlueprintAssignable)
	FOnGaugeReady OnGaugeReady;

	UPROPERTY(BlueprintAssignable)
	FOnChipSelectOpened OnChipSelectOpened;

	UPROPERTY(BlueprintAssignable)
	FOnChipSelectLocked OnChipSelectLocked; // fired once per chip queued into the action queue

	UPROPERTY(BlueprintAssignable)
	FOnChipSelectCancelled OnChipSelectCancelled;

	// Bind this to your L1/R1 or keyboard action. Only succeeds if bGaugeReady is true.
	UFUNCTION(BlueprintCallable, Category = "Gauge")
	bool TryOpenChipSelect();

	// Call once the player has chosen their combo from the hand (after validating
	// with UChipFolderComponent::IsValidCodeCombo on the UI side).
	UFUNCTION(BlueprintCallable, Category = "Gauge")
	bool ConfirmChipSelection(const TArray<FGuid>& SelectedGuids);

	UFUNCTION(BlueprintCallable, Category = "Gauge")
	void CancelChipSelect();

	UFUNCTION(BlueprintCallable, Category = "Gauge")
	bool IsMovementLocked() const { return bSelectMenuOpen; }

protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void ResetGaugeAndDraw();
};
