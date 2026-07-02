#include "MenuGameMode.h"
#include "MainMenuWidget.h"
#include "../../Input/MenuPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AMenuGameMode::AMenuGameMode()
{
    PlayerControllerClass = AMenuPlayerController::StaticClass();
    DefaultPawnClass = nullptr;
}

void AMenuGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (MenuWidgetClass)
    {
        UMainMenuWidget* MenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MenuWidgetClass);
        if (MenuWidget)
        {
            // Assign media and audio properties
            MenuWidget->BackgroundMusic = BackgroundMusic;
            MenuWidget->IntroMediaPlayer = IntroMediaPlayer;
            MenuWidget->IntroMediaSource = IntroMediaSource;

            MenuWidget->AddToViewport(100);

            APlayerController* PC = GetWorld()->GetFirstPlayerController();
            if (PC)
            {
                PC->bShowMouseCursor = true;
                PC->SetInputMode(FInputModeUIOnly());
            }
        }
    }
}

void AMenuGameMode::StartGame()
{
    UGameplayStatics::OpenLevel(this, TEXT("MainGameMap"));
}

void AMenuGameMode::QuitGame()
{
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC)
    {
        UKismetSystemLibrary::QuitGame(this, PC, EQuitPreference::Quit, false);
    }
}
