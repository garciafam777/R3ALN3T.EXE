// Opening engine splash — shown before the studio/main-menu screen.
// Self-contained: builds its visual tree in code, requires NO editor asset.
// Shows a live shader-compile progress bar (0-100%) + "Compiling Shaders: N left"
// so the post-init compile window is not a silent black screen.
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
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    // Held after shaders finish before yielding to the menu.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Splash")
    float DisplayDuration = 3.0f;

    // Hard ceiling: force-dismiss even if compile never reports done (anti-hang).
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Splash")
    float MaxSplashTime = 120.0f;

    // Broadcast when the splash should yield to the main menu (auto or skipped).
    FOnSplashFinished OnSplashFinished;

    UFUNCTION(BlueprintCallable, Category = "Splash")
    void FinishSplash();

protected:
    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

    void BuildLayout();
    bool bFinished = false;

    float SplashElapsed = 0.f;
    float PostCompileElapsed = 0.f;
    bool bShadersDone = false;
    bool bEverCompiled = false;   // saw real compile work at least once

    class UProgressBar* ProgressBar = nullptr;
    class UTextBlock* CompileText = nullptr;
};
