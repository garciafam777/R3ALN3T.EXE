// R3ALN3TGameMode.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "IntroSequence.h"
#include "R3ALN3TGameMode.generated.h"

/**
 * Game mode for R3ALN3T.EXE
 * Handles new game startup, intro sequence, and main game flow
 */
UCLASS()
class R3ALN3TEXE_API AR3ALN3TGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AR3ALN3TGameMode();

	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

	// Called from main menu when player selects "New Game"
	UFUNCTION(BlueprintCallable, Category = "Game|NewGame")
	void StartNewGame();

	// Called from main menu when player selects "Load Game"
	UFUNCTION(BlueprintCallable, Category = "Game|Load")
	void LoadGame(const FString& SaveSlot);

	// Called when intro completes
	UFUNCTION(BlueprintCallable, Category = "Game|Intro")
	void OnIntroComplete();

protected:
	// Reference to intro sequence
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game|Intro")
	TSubclassOf<AIntroSequence> IntroSequenceClass;

	UPROPERTY(BlueprintReadWrite, Category = "Game|Intro")
	AIntroSequence* CurrentIntroSequence;

	// Main game level name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game|Levels")
	FString MainGameLevelName = TEXT("MainGame");

	// Character creation widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game|UI")
	TSubclassOf<class UUserWidget> CharacterCreationWidgetClass;

	bool bGameStarted;

	void SpawnIntroSequence();
};
