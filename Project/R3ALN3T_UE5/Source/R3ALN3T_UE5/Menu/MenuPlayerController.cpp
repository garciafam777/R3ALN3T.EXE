#include "MenuPlayerController.h"
#include "MenuGameMode.h"
#include "Engine/World.h"

void AMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	SetInputMode(FInputModeGameAndUI());
}

void AMenuPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindKey(EKeys::Enter, IE_Pressed, this, &AMenuPlayerController::PressEnter);
	InputComponent->BindKey(EKeys::Escape, IE_Pressed, this, &AMenuPlayerController::PressEscape);
}

void AMenuPlayerController::PressEnter()
{
	if (AMenuGameMode* GM = GetWorld()->GetAuthGameMode<AMenuGameMode>())
	{
		GM->StartGame();
	}
}

void AMenuPlayerController::PressEscape()
{
	if (AMenuGameMode* GM = GetWorld()->GetAuthGameMode<AMenuGameMode>())
	{
		GM->QuitGame();
	}
}
