#include "MenuGameMode.h"
#include "MainMenuWidget.h"
#include "EngineSplashWidget.h"
#include "../../Input/MenuPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AMenuGameMode::AMenuGameMode()
{
    PlayerControllerClass = AMenuPlayerController::StaticClass();
    DefaultPawnClass = nullptr;
    EngineSplashClass = UEngineSplashWidget::StaticClass();
}

void AMenuGameMode::BeginPlay()
{
    Super::BeginPlay();

    // Opening engine splash first (if set). Menu (studio screen) spawns after splash finishes.
    if (EngineSplashClass)
    {
        if (UEngineSplashWidget* Splash = CreateWidget<UEngineSplashWidget>(GetWorld(), EngineSplashClass))
        {
            Splash->AddToViewport(200);
            Splash->OnSplashFinished.AddLambda([this]()
            {
                ShowMainMenu();
            });
            return;
        }
    }

    ShowMainMenu();
}

void AMenuGameMode::ShowMainMenu()
{
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
