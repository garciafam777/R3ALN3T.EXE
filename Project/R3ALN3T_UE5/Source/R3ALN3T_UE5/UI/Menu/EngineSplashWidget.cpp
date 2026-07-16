#include "EngineSplashWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/PanelSlot.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Blueprint/WidgetTree.h"
#include "R3ALShaderStatics.h"

void UEngineSplashWidget::NativeConstruct()
{
    Super::NativeConstruct();
    BuildLayout();
}

void UEngineSplashWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    if (bFinished) return;

    SplashElapsed += InDeltaTime;

    const bool bCompiling = UR3ALShaderStatics::IsCompilingShaders();
    const float Pct = UR3ALShaderStatics::GetShaderCompileProgress();
    const int32 Remaining = UR3ALShaderStatics::NumPrecompilesRemaining();

    if (ProgressBar)
    {
        ProgressBar->SetPercent(FMath::Clamp(Pct, 0.f, 1.f));
    }
    if (CompileText)
    {
        if (bCompiling || Remaining > 0)
        {
            bEverCompiled = true;
            CompileText->SetText(FText::Format(
                NSLOCTEXT("Splash", "Compiling", "Compiling Shaders: {0} left"),
                FText::AsNumber(Remaining)));
        }
        else
        {
            CompileText->SetText(NSLOCTEXT("Splash", "Ready", "Shaders ready"));
        }
    }

    // Only arm the post-compile hold once we've actually seen work (or enough
    // time passed that a warm DDC clearly needs no compile). Prevents a cold
    // start from dismissing before the compile even begins reporting.
    if (!bCompiling && Remaining == 0)
    {
        if (bEverCompiled || SplashElapsed > 3.f)
        {
            if (!bShadersDone)
            {
                bShadersDone = true;
                PostCompileElapsed = 0.f;
                if (ProgressBar) ProgressBar->SetPercent(1.f);
            }
            else
            {
                PostCompileElapsed += InDeltaTime;
            }
        }
    }

    if ((bShadersDone && PostCompileElapsed >= DisplayDuration) ||
        SplashElapsed >= MaxSplashTime)
    {
        FinishSplash();
    }
}

void UEngineSplashWidget::FinishSplash()
{
    if (bFinished) return;
    bFinished = true;
    RemoveFromParent();
    OnSplashFinished.Broadcast();
}

FReply UEngineSplashWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    FinishSplash();
    return FReply::Handled();
}

FReply UEngineSplashWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    FinishSplash();
    return FReply::Handled();
}

void UEngineSplashWidget::BuildLayout()
{
    const FString Roboto = FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf");

    // Root canvas (full-viewport, no anchoring assumptions).
    UCanvasPanel* Root = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
    if (UCanvasPanelSlot* RootSlot = Cast<UCanvasPanelSlot>(Root->Slot))
    {
        RootSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
        RootSlot->SetOffsets(FMargin(0.f));
    }
    WidgetTree->RootWidget = Root;

    // Black backdrop.
    UImage* Backdrop = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
    Backdrop->SetColorAndOpacity(FLinearColor::Black);
    if (UCanvasPanelSlot* BdSlot = Root->AddChildToCanvas(Backdrop))
    {
        BdSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
        BdSlot->SetOffsets(FMargin(0.f));
    }

    // Title.
    UTextBlock* Title = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
    Title->SetText(FText::FromString(TEXT("POWERED BY UNREAL ENGINE")));
    Title->SetJustification(ETextJustify::Center);
    Title->SetColorAndOpacity(FSlateColor(FLinearColor::White));
    Title->SetFont(FSlateFontInfo(Roboto, 28));
    if (UCanvasPanelSlot* TitleSlot = Root->AddChildToCanvas(Title))
    {
        TitleSlot->SetAnchors(FAnchors(0.5f, 0.42f, 0.5f, 0.42f));
        TitleSlot->SetAutoSize(true);
        TitleSlot->SetAlignment(FVector2D(0.5f, 0.5f));
    }

    // Subtitle.
    UTextBlock* Sub = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
    Sub->SetText(FText::FromString(TEXT("R3ALN3T.EXE  |  6th Gear Studios")));
    Sub->SetJustification(ETextJustify::Center);
    Sub->SetColorAndOpacity(FSlateColor(FLinearColor::White));
    Sub->SetFont(FSlateFontInfo(Roboto, 18));
    if (UCanvasPanelSlot* SubSlot = Root->AddChildToCanvas(Sub))
    {
        SubSlot->SetAnchors(FAnchors(0.5f, 0.52f, 0.5f, 0.52f));
        SubSlot->SetAutoSize(true);
        SubSlot->SetAlignment(FVector2D(0.5f, 0.5f));
    }

    // Progress bar (bottom, full width minus margins).
    ProgressBar = WidgetTree->ConstructWidget<UProgressBar>(UProgressBar::StaticClass());
    ProgressBar->SetPercent(0.f);
    ProgressBar->SetFillColorAndOpacity(FLinearColor(0.f, 0.6f, 1.f, 1.f));
    if (UCanvasPanelSlot* BarSlot = Root->AddChildToCanvas(ProgressBar))
    {
        BarSlot->SetAnchors(FAnchors(0.15f, 0.85f, 0.85f, 0.85f));
        BarSlot->SetSize(FVector2D(0.f, 8.f));
    }

    // Compile status text (below the bar).
    CompileText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
    CompileText->SetText(FText::FromString(TEXT("Preparing shaders...")));
    CompileText->SetJustification(ETextJustify::Center);
    CompileText->SetColorAndOpacity(FSlateColor(FLinearColor(0.8f, 0.8f, 0.8f, 1.f)));
    CompileText->SetFont(FSlateFontInfo(Roboto, 14));
    if (UCanvasPanelSlot* TxtSlot = Root->AddChildToCanvas(CompileText))
    {
        TxtSlot->SetAnchors(FAnchors(0.5f, 0.90f, 0.5f, 0.90f));
        TxtSlot->SetAutoSize(true);
        TxtSlot->SetAlignment(FVector2D(0.5f, 0.5f));
    }
}
