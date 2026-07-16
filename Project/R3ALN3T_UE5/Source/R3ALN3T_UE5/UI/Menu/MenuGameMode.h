// Isolated menu runtime — prevents character entity initialization during title/splash screens.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGameMode.generated.h"

class UMainMenuWidget;
class UEngineSplashWidget;
class USoundBase;
class UMediaPlayer;
class UMediaSource;

UCLASS()
class R3ALN3T_UE5_API AMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMenuGameMode();

	virtual void BeginPlay() override;

	// Spawns the studio/main-menu screen. Called directly when no splash is set,
	// or deferred until the opening splash finishes.
	void ShowMainMenu();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	TSubclassOf<UMainMenuWidget> MenuWidgetClass;

	// Opening engine splash, shown before the studio/main-menu screen.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Splash")
	TSubclassOf<UEngineSplashWidget> EngineSplashClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	USoundBase* BackgroundMusic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cinematic")
	UMediaPlayer* IntroMediaPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cinematic")
	UMediaSource* IntroMediaSource;

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void StartGame();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void QuitGame();
};
