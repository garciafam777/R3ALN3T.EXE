// GridMoverComponent.cpp
#include "GridMoverComponent.h"
#include "BattleGridManager.h"
#include "BattleStateComponent.h"
#include "GameFramework/Actor.h"

UGridMoverComponent::UGridMoverComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

bool UGridMoverComponent::RequestMove(EGridDirection Direction)
{
	if (BattleState && BattleState->IsMovementLocked())
	{
		return false; // this unit's own select-menu is open; opponent's mover is unaffected
	}

	FGridCoord Target = CurrentCoord;
	switch (Direction)
	{
		case EGridDirection::Up:    Target.Row -= 1; break;
		case EGridDirection::Down:  Target.Row += 1; break;
		case EGridDirection::Left:  Target.Col -= 1; break;
		case EGridDirection::Right: Target.Col += 1; break;
	}
	return RequestMoveTo(Target, false);
}

bool UGridMoverComponent::RequestMoveTo(FGridCoord TargetCoord, bool bIsAbilityCrossing)
{
	if (BattleState && BattleState->IsMovementLocked())
	{
		return false;
	}

	if (bIsMoving || !GridManager) return false;
	if (!GridManager->IsValidCoord(TargetCoord)) return false;

	const bool bCrossing = GridManager->CrossesMedian(CurrentCoord, TargetCoord);
	if (bCrossing && !bIsAbilityCrossing && !bCanCrossMedian)
	{
		return false; // normal movement can't cross the median, only abilities can
	}

	// Side-switching abilities skip the walkable/occupied check on the destination --
	// it's an attack landing spot, not a stand-and-wait spot. Normal moves still need it.
	if (!bCrossing && !GridManager->IsWalkable(TargetCoord))
	{
		return false;
	}

	GridManager->SetPanelOccupied(CurrentCoord, false, FLinearColor::White);

	MoveStart = GetOwner()->GetActorLocation();
	MoveEnd = GridManager->GridToWorld(TargetCoord);
	MoveAlpha = 0.f;
	bIsMoving = true;
	PendingCoord = TargetCoord;
	bPendingCrossing = bCrossing;

	return true;
}

void UGridMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!bIsMoving) return;

	MoveAlpha += DeltaTime / MoveDuration;
	const float Eased = FMath::InterpEaseInOut(0.f, 1.f, FMath::Clamp(MoveAlpha, 0.f, 1.f), 2.f);
	GetOwner()->SetActorLocation(FMath::Lerp(MoveStart, MoveEnd, Eased));

	if (MoveAlpha >= 1.f)
	{
		bIsMoving = false;
		const FGridCoord OldCoord = CurrentCoord;
		CurrentCoord = PendingCoord;

		if (!bPendingCrossing && GridManager)
		{
			GridManager->SetPanelOccupied(CurrentCoord, true, FLinearColor::White);
		}

		OnMoveComplete.Broadcast(OldCoord);

		if (bPendingCrossing)
		{
			OnSideSwitchAttack.Broadcast(CurrentCoord); // hook your damage/VFX here
		}
	}
}
