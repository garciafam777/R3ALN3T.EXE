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
	// Default the main-menu widget to the authored WBP (populates BindWidget slots).
	// Without this, ShowMainMenu()'s `if (MenuWidgetClass)` is always false -> black screen.
	static ConstructorHelpers::FClassFinder<UUserWidget> MenuBP(TEXT("/Game/R3ALN3T/Core/UI/Menus/WBP_MainMenu"));
	if (MenuBP.Succeeded())
	{
		MenuWidgetClass = MenuBP.Class;
	}
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
			// Fallback: if the splash's own auto-dismiss timer never fires (e.g. world
			// timer unavailable at construct), force the menu after DisplayDuration + slack.
			if (GetWorld())
			{
				FTimerHandle SplashFallback;
				GetWorld()->GetTimerManager().SetTimer(SplashFallback, FTimerDelegate::CreateLambda([this]()
				{
					ShowMainMenu();
				}), 5.0f, false);
			}
			return;
		}
	}

	ShowMainMenu();
}

void AMenuGameMode::ShowMainMenu()
{
	static bool bMenuShown = false;
	if (bMenuShown) return;
	bMenuShown = true;

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
