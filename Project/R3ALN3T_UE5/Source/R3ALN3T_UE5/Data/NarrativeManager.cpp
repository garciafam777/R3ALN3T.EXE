#include "NarrativeManager.h"

void UNarrativeManager::LoadStoryTable(UDataTable* InStoryTable)
{
	StoryTable = InStoryTable;
}

void UNarrativeManager::LoadChoiceTable(UDataTable* InChoiceTable)
{
	ChoiceTable = InChoiceTable;
}

void UNarrativeManager::LoadEnemyTable(UDataTable* InEnemyTable)
{
	EnemyTable = InEnemyTable;
}

bool UNarrativeManager::GetStoryRow(FName NodeID, FNarrativeStoryRow& OutRow) const
{
	if (!StoryTable) return false;
	static const FString Context(TEXT("GetStoryRow"));
	FNarrativeStoryRow* Row = StoryTable->FindRow<FNarrativeStoryRow>(NodeID, Context);
	if (!Row) return false;
	OutRow = *Row;
	return true;
}

TArray<FNarrativeChoiceRow> UNarrativeManager::GetChoicesForNode(FName NodeID) const
{
	TArray<FNarrativeChoiceRow> Results;
	if (!ChoiceTable) return Results;

	TArray<FNarrativeChoiceRow*> AllRows;
	ChoiceTable->GetAllRows<FNarrativeChoiceRow>(TEXT("GetChoicesForNode"), AllRows);

	for (const FNarrativeChoiceRow* Row : AllRows)
	{
		if (Row && Row->NodeID == NodeID)
		{
			Results.Add(*Row);
		}
	}
	Results.Sort([](const FNarrativeChoiceRow& A, const FNarrativeChoiceRow& B) {
		return A.ChoiceIndex < B.ChoiceIndex;
	});
	return Results;
}

bool UNarrativeManager::GetEnemyRow(FName EnemyID, FEnemyRow& OutRow) const
{
	if (!EnemyTable) return false;
	static const FString Context(TEXT("GetEnemyRow"));
	FEnemyRow* Row = EnemyTable->FindRow<FEnemyRow>(EnemyID, Context);
	if (!Row) return false;
	OutRow = *Row;
	return true;
}

TArray<FName> UNarrativeManager::GetStoryNodeIDsByAct(int32 ActIndex) const
{
	TArray<FName> Results;
	if (!StoryTable) return Results;

	TArray<FNarrativeStoryRow*> AllRows;
	StoryTable->GetAllRows<FNarrativeStoryRow>(TEXT("GetStoryNodeIDsByAct"), AllRows);

	for (const FNarrativeStoryRow* Row : AllRows)
	{
		if (Row && Row->ActIndex == ActIndex)
		{
			Results.Add(Row->NodeID);
		}
	}
	return Results;
}
