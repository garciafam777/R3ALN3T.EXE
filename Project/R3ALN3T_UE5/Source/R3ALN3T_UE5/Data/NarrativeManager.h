// Data-driven narrative manager — loads story/choice/enemy data from UDataTable assets
// via Soft Object References so the runtime can swap content without recompilation.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DataTypes.h"
#include "../Mythos/MythosGameTypes.h"
#include "NarrativeManager.generated.h"

UCLASS(BlueprintType)
class R3ALN3T_UE5_API UNarrativeManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Narrative")
	void LoadStoryTable(UDataTable* InStoryTable);

	UFUNCTION(BlueprintCallable, Category = "Narrative")
	void LoadChoiceTable(UDataTable* InChoiceTable);

	UFUNCTION(BlueprintCallable, Category = "Narrative")
	void LoadEnemyTable(UDataTable* InEnemyTable);

	UFUNCTION(BlueprintCallable, Category = "Narrative")
	bool GetStoryRow(FName NodeID, FNarrativeStoryRow& OutRow) const;

	UFUNCTION(BlueprintCallable, Category = "Narrative")
	TArray<FNarrativeChoiceRow> GetChoicesForNode(FName NodeID) const;

	UFUNCTION(BlueprintCallable, Category = "Narrative")
	bool GetEnemyRow(FName EnemyID, FEnemyRow& OutRow) const;

	UFUNCTION(BlueprintCallable, Category = "Narrative")
	TArray<FName> GetStoryNodeIDsByAct(int32 ActIndex) const;

private:
	UPROPERTY()
	UDataTable* StoryTable = nullptr;

	UPROPERTY()
	UDataTable* ChoiceTable = nullptr;

	UPROPERTY()
	UDataTable* EnemyTable = nullptr;
};
