// ChipFolderComponent.cpp
#include "ChipFolderComponent.h"
#include "Algo/RandomShuffle.h"
#include "../../../Core/Types/BattleGridTypes.h"

UChipFolderComponent::UChipFolderComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UChipFolderComponent::ShuffleFolder()
{
	Algo::RandomShuffle(Folder);
}

void UChipFolderComponent::DrawHand()
{
	// Top up the hand to HandSize, pulling from the front of the (shuffled) folder.
	// Cards used in the previous select round should already have been removed
	// via RemoveFromHandByGuid before this is called again.
	while (Hand.Num() < HandSize && Folder.Num() > 0)
	{
		Hand.Add(Folder[0]);
		Folder.RemoveAt(0);
	}
}

const FChipInstance* UChipFolderComponent::FindInHand(const FGuid& Guid) const
{
	return Hand.FindByPredicate([&Guid](const FChipInstance& C) { return C.InstanceGuid == Guid; });
}

bool UChipFolderComponent::IsValidCodeCombo(const TArray<FGuid>& CandidateGuids) const
{
	if (CandidateGuids.Num() <= 1) return true; // single-chip selection is always legal

	EChipCode LockedCode = EChipCode::Star;
	bool bLockedCodeSet = false;

	for (const FGuid& Guid : CandidateGuids)
	{
		const FChipInstance* Chip = FindInHand(Guid);
		if (!Chip) return false; // selection references a chip not in hand — reject

		if (Chip->Code == EChipCode::Star) continue; // wildcard never conflicts

		if (!bLockedCodeSet)
		{
			LockedCode = Chip->Code;
			bLockedCodeSet = true;
		}
		else if (Chip->Code != LockedCode)
		{
			return false; // two different non-wildcard codes in the same combo — illegal
		}
	}
	return true;
}

TArray<FGuid> UChipFolderComponent::GetLegalNextSelections(const TArray<FGuid>& AlreadySelected) const
{
	TArray<FGuid> Legal;

	// Work out what code (if any) the current selection has locked in.
	EChipCode LockedCode = EChipCode::Star;
	bool bLockedCodeSet = false;
	for (const FGuid& Guid : AlreadySelected)
	{
		const FChipInstance* Chip = FindInHand(Guid);
		if (Chip && Chip->Code != EChipCode::Star)
		{
			LockedCode = Chip->Code;
			bLockedCodeSet = true;
			break;
		}
	}

	for (const FChipInstance& Chip : Hand)
	{
		if (AlreadySelected.Contains(Chip.InstanceGuid)) continue; // already picked

		if (!bLockedCodeSet || Chip.Code == EChipCode::Star || Chip.Code == LockedCode)
		{
			Legal.Add(Chip.InstanceGuid);
		}
	}
	return Legal;
}

bool UChipFolderComponent::RemoveFromHandByGuid(const FGuid& InstanceGuid, FChipInstance& OutRemoved)
{
	const int32 Index = Hand.IndexOfByPredicate([&InstanceGuid](const FChipInstance& C) { return C.InstanceGuid == InstanceGuid; });
	if (Index == INDEX_NONE) return false;

	OutRemoved = Hand[Index];
	Hand.RemoveAt(Index);
	return true;
}
