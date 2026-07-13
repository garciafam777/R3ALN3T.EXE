// BattleStateComponent.cpp
#include "BattleStateComponent.h"
#include "ChipFolderComponent.h"
#include "GridMoverComponent.h"

UBattleStateComponent::UBattleStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBattleStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Gauge keeps filling in real time regardless of grid movement state — it is NOT
	// paused by movement, only the select menu pauses things, and only for this unit.
	if (!bGaugeReady && !bSelectMenuOpen)
	{
		GaugeAlpha = FMath::Clamp(GaugeAlpha + DeltaTime / GaugeFillDuration, 0.f, 1.f);
		if (GaugeAlpha >= 1.f)
		{
			bGaugeReady = true;
			OnGaugeReady.Broadcast(); // HUD should flash/pulse the gauge bar here, e.g. the "55%" -> glowing full state
		}
	}
}

bool UBattleStateComponent::TryOpenChipSelect()
{
	if (!bGaugeReady || bSelectMenuOpen) return false;

	bSelectMenuOpen = true;
	if (FolderComponent)
	{
		FolderComponent->DrawHand(); // top up hand if it's short
	}
	if (MoverComponent)
	{
		// Movement for THIS unit pauses — opponent is unaffected and keeps moving/acting.
	}

	OnChipSelectOpened.Broadcast();
	return true;
}

bool UBattleStateComponent::ConfirmChipSelection(const TArray<FGuid>& SelectedGuids)
{
	if (!bSelectMenuOpen || !FolderComponent) return false;

	if (!FolderComponent->IsValidCodeCombo(SelectedGuids))
	{
		return false; // UI should already prevent this via GetLegalNextSelections, this is the hard backstop
	}

	for (const FGuid& Guid : SelectedGuids)
	{
		FChipInstance Removed;
		if (FolderComponent->RemoveFromHandByGuid(Guid, Removed))
		{
			OnChipSelectLocked.Broadcast(Removed); // hook into your action-queue / cast system here
		}
	}

	bSelectMenuOpen = false;
	ResetGaugeAndDraw();
	return true;
}

void UBattleStateComponent::CancelChipSelect()
{
	if (!bSelectMenuOpen) return;
	bSelectMenuOpen = false;
	OnChipSelectCancelled.Broadcast();
	// Note: gauge stays at bGaugeReady = true, alpha = 1 — cancelling doesn't cost the
	// charge, player can reopen immediately. Change this if you want cancel to be punishing.
}

void UBattleStateComponent::ResetGaugeAndDraw()
{
	bGaugeReady = false;
	GaugeAlpha = 0.f;
}
