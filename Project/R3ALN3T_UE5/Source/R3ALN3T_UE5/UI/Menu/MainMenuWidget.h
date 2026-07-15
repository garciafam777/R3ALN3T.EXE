// R3ALN3T_UE5 MainMenuWidget.h
// UMG-based main menu with background music and intro cinematic trigger.
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "MediaPlayer.h"
#include "MediaSource.h"
class UCreditsWidget;
#include "MainMenuWidget.generated.h"

UCLASS()
class R3ALN3T_UE5_API UMainMenuWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UButton* NewGameButton;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UButton* ContinueButton;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UButton* QuitButton;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UButton* CreditsButton;

    // Credits panel to spawn when CreditsButton is pressed (set in WBP_MainMenu).
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
    TSubclassOf<UCreditsWidget> CreditsWidgetClass;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UButton* CreditsButton;

    // Credits widget to spawn when CreditsButton is clicked.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
    TSubclassOf<UUserWidget> CreditsWidgetClass;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UTextBlock* TitleText;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UImage* BackgroundImage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    USoundBase* BackgroundMusic;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cinematic")
    UMediaPlayer* IntroMediaPlayer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cinematic")
    UMediaSource* IntroMediaSource;

    UFUNCTION(BlueprintCallable, Category = "Menu")
    void PlayIntroCinematic();

    UFUNCTION(BlueprintCallable, Category = "Menu")
    void OnIntroFinished();

protected:
    UFUNCTION()
    void OnNewGameClicked();

    UFUNCTION()
    void OnContinueClicked();

    UFUNCTION()
    void OnQuitClicked();

    UFUNCTION()
    void OnCreditsClicked();

    UFUNCTION()
    void OnCreditsClicked();

private:
    UPROPERTY()
    UAudioComponent* MusicComponent;

    void StartBackgroundMusic();
    void StopBackgroundMusic();
};
