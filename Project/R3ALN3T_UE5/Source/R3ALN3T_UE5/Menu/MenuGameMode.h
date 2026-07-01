// Isolated menu runtime — prevents character entity initialization during title/splash screens.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGameMode.generated.h"

UCLASS()
class R3ALN3T_UE5_API AMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMenuGameMode();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void StartGame(); // transitions to the main game map / level

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void QuitGame();
};
