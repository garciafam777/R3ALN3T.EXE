// GridMoverComponent.h
// Discrete panel-to-panel movement (MMBN-style, NOT continuous free movement).
// Both NetP and viruses/bosses use this same component. Normal units cannot
// cross the median; units with bCanCrossMedian = true can step directly onto
// the opponent's side to deliver an attack.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BattleGridTypes.h"
#include "GridMoverComponent.generated.h"

class ABattleGridManager;
class UBattleStateComponent;

UENUM(BlueprintType)
enum class EGridDirection : uint8
{
	Up, Down, Left, Right
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGridMoveComplete, FGridCoord, OldCoord);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSideSwitchAttack, FGridCoord, TargetCoord);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class R3ALN3TEXE_API UGridMoverComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGridMoverComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GridMove")
	ABattleGridManager* GridManager;

	// Optional link to this unit's own gauge/select state -- when its select menu
	// is open, movement locks for THIS unit only. Leave null for units that don't
	// use the gauge system (e.g. simple viruses driven purely by AI timers).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GridMove")
	UBattleStateComponent* BattleState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GridMove")
	FGridCoord CurrentCoord;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GridMove")
	bool bCanCrossMedian = false; // true for dash-attackers/bosses with that ability

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GridMove")
	float MoveDuration = 0.18f; // panel-to-panel lerp time, tune for feel

	UPROPERTY(BlueprintAssignable)
	FOnGridMoveComplete OnMoveComplete;

	UPROPERTY(BlueprintAssignable)
	FOnSideSwitchAttack OnSideSwitchAttack; // fired when a median-crossing move lands, hook damage/VFX here

	UFUNCTION(BlueprintCallable, Category = "GridMove")
	bool RequestMove(EGridDirection Direction);

	UFUNCTION(BlueprintCallable, Category = "GridMove")
	bool RequestMoveTo(FGridCoord TargetCoord, bool bIsAbilityCrossing);

	UFUNCTION(BlueprintCallable, Category = "GridMove")
	bool IsMoving() const { return bIsMoving; }

protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool bIsMoving = false;
	FVector MoveStart;
	FVector MoveEnd;
	float MoveAlpha = 0.f;
	FGridCoord PendingCoord;
	bool bPendingCrossing = false;
};
