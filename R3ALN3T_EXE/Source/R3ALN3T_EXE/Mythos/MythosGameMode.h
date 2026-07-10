// Playable game shell for R3ALN3T.EXE.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MythosGameTypes.h"
#include "MythosGameMode.generated.h"

UCLASS()
class R3ALN3T_EXE_API AMythosGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMythosGameMode();

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "R3ALN3T")
	FMythosRunState Run;

	UPROPERTY(BlueprintReadOnly, Category = "R3ALN3T")
	int32 ActiveStoryNode = 0;

	UPROPERTY(BlueprintReadOnly, Category = "R3ALN3T")
	FString BattleEnemyName;

	UPROPERTY(BlueprintReadOnly, Category = "R3ALN3T")
	FString BattleEnemyText;

	UPROPERTY(BlueprintReadOnly, Category = "R3ALN3T")
	int32 BattleEnemyHP = 0;

	UPROPERTY(BlueprintReadOnly, Category = "R3ALN3T")
	int32 BattleEnemyMaxHP = 0;

	UPROPERTY(BlueprintReadOnly, Category = "R3ALN3T")
	int32 BattleShield = 0;

	UPROPERTY(BlueprintReadOnly, Category = "R3ALN3T")
	TArray<FString> BattleLog;

	UFUNCTION(BlueprintCallable, Category = "R3ALN3T")
	void NewRun();

	UFUNCTION(BlueprintCallable, Category = "R3ALN3T")
	void ChooseCareerByIndex(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "R3ALN3T")
	void ChooseElementByIndex(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "R3ALN3T")
	void WorkShift();

	UFUNCTION(BlueprintCallable, Category = "R3ALN3T")
	void EnterCurrentStoryNode();

	UFUNCTION(BlueprintCallable, Category = "R3ALN3T")
	void ChooseStoryOption(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "R3ALN3T")
	void ResolveBattleAction(EMythosBattleAction Action);

	UFUNCTION(BlueprintCallable, Category = "R3ALN3T")
	void ResolveEndingByIndex(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "R3ALN3T")
	void PostGameAction(int32 Index);

	const TArray<FMythosCareerData>& GetCareers() const { return Careers; }
	const TArray<FString>& GetElements() const { return ElementNames; }
	const TArray<FMythosStoryNode>& GetStoryNodes() const { return StoryNodes; }
	FString GetFactionName(EMythosFaction Faction) const;
	FString GetCareerName() const;
	FString GetElementName() const;
	FString GetRankName() const;
	FString GetSuggestedEnding() const;

private:
	TArray<FMythosCareerData> Careers;
	TArray<FString> ElementNames;
	TArray<FMythosStoryNode> StoryNodes;
	TArray<FString> EndingNames;
	TArray<FString> EndingBodies;
	int32 PendingNextNode = 0;

	void BuildContent();
	void AddLog(const FString& Text);
	void AddInventory(const FString& Item);
	void ApplyFaction(EMythosFaction Faction, int32 Delta);
	int32 GetFactionScore(EMythosFaction Faction) const;
	EMythosFaction GetTopFaction() const;
	bool IsFactionSpreadBalanced() const;
	void StartBattle(int32 EnemyIndex, int32 NextNode);
	void CompleteBattle();
	int32 SuggestEndingIndex() const;
	void ApplyElementPerkAfterDay();
};
