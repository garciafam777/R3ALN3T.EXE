#include "MenuGameMode.h"
#include "MenuPlayerController.h"
#include "Kismet/GameplayStatics.h"

AMenuGameMode::AMenuGameMode()
{
	PlayerControllerClass = AMenuPlayerController::StaticClass();
	DefaultPawnClass = nullptr;
}

void AMenuGameMode::BeginPlay()
{
	Super::BeginPlay();
	// Menu widgets are spawned from the player controller or level BP
}

void AMenuGameMode::StartGame()
{
	// Transition to the primary game map
	UGameplayStatics::OpenLevel(this, TEXT("MainGameMap"));
}

void AMenuGameMode::QuitGame()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->ConsoleCommand(TEXT("quit"));
	}
}
