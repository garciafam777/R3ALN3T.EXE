// ChipFolderComponent.h
// Owns a unit's 30-chip folder, draws a hand, and enforces the Greek-letter
// code-share rule when the player is selecting multiple chips to lock in at once:
// all selected chips must share a single EChipCode OR be EChipCode::Star.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BattleChipTypes.h"
#include "BattleGridTypes.h"
#include "ChipFolderComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class R3ALN3TEXE_API UChipFolderComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UChipFolderComponent();

	// Full folder, MMBN standard is 30 chips
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Folder")
	TArray<FChipInstance> Folder;

	// Cards currently drawn into hand, waiting to be picked when the gauge opens select
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Folder")
	TArray<FChipInstance> Hand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Folder")
	int32 HandSize = 5; // MMBN standard draw

	UFUNCTION(BlueprintCallable, Category = "Folder")
	void ShuffleFolder();

	UFUNCTION(BlueprintCallable, Category = "Folder")
	void DrawHand();

	// Returns true if every chip in CandidateGuids shares a code (or is Star).
	// This is the actual rule enforcement — call it BEFORE locking in a multi-chip selection.
	UFUNCTION(BlueprintCallable, Category = "Folder")
	bool IsValidCodeCombo(const TArray<FGuid>& CandidateGuids) const;

	// Convenience: given chips already selected, returns which remaining hand chips
	// are LEGAL to add next (same code, Star, or hand is empty-selection state).
	// Drive your UI's "greyed out vs selectable" chip highlighting from this.
	UFUNCTION(BlueprintCallable, Category = "Folder")
	TArray<FGuid> GetLegalNextSelections(const TArray<FGuid>& AlreadySelected) const;

	UFUNCTION(BlueprintCallable, Category = "Folder")
	bool RemoveFromHandByGuid(const FGuid& InstanceGuid, FChipInstance& OutRemoved);

private:
	const FChipInstance* FindInHand(const FGuid& Guid) const;
};
