// MainMenuWidget.cpp
#include "MainMenuWidget.h"
#include "MenuGameMode.h"
#include "../../Core/Managers/R3ALN3TGameInstance.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MediaPlayer.h"
#include "MediaSource.h"
#include "Engine/World.h"
#include "TimerManager.h"

void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (NewGameButton)
        NewGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnNewGameClicked);
    if (ContinueButton)
        ContinueButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnContinueClicked);
    if (QuitButton)
        QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitClicked);

    // Start with intro cinematic
    if (IntroMediaPlayer && IntroMediaSource)
    {
        PlayIntroCinematic();
    }
    else
    {
        StartBackgroundMusic();
    }
}

void UMainMenuWidget::PlayIntroCinematic()
{
    if (IntroMediaPlayer && IntroMediaSource)
    {
        IntroMediaPlayer->OpenSource(IntroMediaSource);
        IntroMediaPlayer->Play();

        SetVisibility(ESlateVisibility::Collapsed);

        // Poll for end via timer (OnMediaEnded not available in UE5.8 as delegate)
        FTimerHandle TimerHandle;
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
        {
            if (IntroMediaPlayer && !IntroMediaPlayer->IsPlaying() && IntroMediaPlayer->IsPreparing())
            {
                // Still loading
                return;
            }
            if (IntroMediaPlayer && !IntroMediaPlayer->IsPlaying())
            {
                OnIntroFinished();
            }
        }, 0.5f, true);
    }
}

void UMainMenuWidget::OnIntroFinished()
{
    SetVisibility(ESlateVisibility::Visible);
    StartBackgroundMusic();
}

void UMainMenuWidget::StartBackgroundMusic()
{
    if (!BackgroundMusic) return;

    MusicComponent = NewObject<UAudioComponent>(this);
    if (MusicComponent)
    {
        MusicComponent->Sound = BackgroundMusic;
        MusicComponent->bAutoActivate = true;
        MusicComponent->bIsUISound = true;
        MusicComponent->RegisterComponent();
        MusicComponent->Play();
    }
}

void UMainMenuWidget::StopBackgroundMusic()
{
    if (MusicComponent && MusicComponent->IsPlaying())
    {
        MusicComponent->Stop();
    }
}

void UMainMenuWidget::OnNewGameClicked()
{
    StopBackgroundMusic();
    AMenuGameMode* GM = Cast<AMenuGameMode>(GetWorld()->GetAuthGameMode());
    if (GM)
    {
        GM->StartGame();
    }
}

void UMainMenuWidget::OnContinueClicked()
{
    StopBackgroundMusic();
    UR3ALN3TGameInstance* GI = Cast<UR3ALN3TGameInstance>(GetWorld()->GetGameInstance());
    if (GI)
    {
        for (int32 i = 0; i < 10; ++i)
        {
            if (GI->HasSaveData(i))
            {
                GI->LoadGame(i);
                UGameplayStatics::OpenLevel(this, TEXT("MainGameMap"));
                return;
            }
        }
    }
    OnNewGameClicked();
}

void UMainMenuWidget::OnQuitClicked()
{
    StopBackgroundMusic();
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC)
    {
        UKismetSystemLibrary::QuitGame(this, PC, EQuitPreference::Quit, false);
    }
}
