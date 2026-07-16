// Opening engine splash — shown before the studio/main-menu screen.
// Self-contained: builds its visual tree in code, requires NO editor asset.
// The native class is directly instantiable (MenuGameMode defaults EngineSplashClass to it),
// so a styled WBP can later override it without code changes.
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EngineSplashWidget.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnSplashFinished);

UCLASS()
class R3ALN3T_UE5_API UEngineSplashWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    // Seconds the splash stays before auto-dismiss. Designer can override on a BP child.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Splash")
    float DisplayDuration = 3.0f;

    // Broadcast when the splash should yield to the main menu (auto or skipped).
    FOnSplashFinished OnSplashFinished;

    UFUNCTION(BlueprintCallable, Category = "Splash")
    void FinishSplash();

protected:
    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

    void BuildLayout();
    bool bFinished = false;
};
