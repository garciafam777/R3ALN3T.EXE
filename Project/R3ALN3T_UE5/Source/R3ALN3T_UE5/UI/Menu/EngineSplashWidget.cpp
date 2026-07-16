// Opening engine splash implementation. Code-built layout (no editor asset dependency).
#include "EngineSplashWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"

void UEngineSplashWidget::NativeConstruct()
{
    Super::NativeConstruct();
    BuildLayout();
    SetKeyboardFocus();

    if (DisplayDuration > 0.f)
    {
        FTimerHandle Dummy;
        GetWorld()->GetTimerManager().SetTimer(Dummy, this, &UEngineSplashWidget::FinishSplash, DisplayDuration, false);
    }
}

void UEngineSplashWidget::BuildLayout()
{
    // Full-screen black backdrop.
    UBorder* Backdrop = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass(), FName("Backdrop"));
    Backdrop->SetBrushColor(FLinearColor::Black);

    UOverlay* Root = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass(), FName("Root"));
    WidgetTree->RootWidget = Root;
    Root->AddChild(Backdrop);

    UVerticalBox* VBox = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass(), FName("VBox"));
    if (UOverlaySlot* VSlot = Cast<UOverlaySlot>(Root->AddChild(VBox)))
    {
        VSlot->SetHorizontalAlignment(HAlign_Center);
        VSlot->SetVerticalAlignment(VAlign_Center);
    }

    auto MakeText = [&](const FText& InText, float Size) -> UTextBlock*
    {
        UTextBlock* T = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), FName(*InText.ToString()));
        T->SetText(InText);
        T->SetColorAndOpacity(FSlateColor(FLinearColor::White));
        FSlateFontInfo Font = T->GetFont();
        Font.Size = Size;
        T->SetFont(Font);
        T->SetJustification(ETextJustify::Center);
        return T;
    };

    if (UVerticalBoxSlot* S1 = Cast<UVerticalBoxSlot>(VBox->AddChild(MakeText(FText::FromString(TEXT("POWERED BY")), 18))))
        S1->SetPadding(FMargin(0.f, 0.f, 0.f, 8.f));
    if (UVerticalBoxSlot* S2 = Cast<UVerticalBoxSlot>(VBox->AddChild(MakeText(FText::FromString(TEXT("UNREAL ENGINE")), 64))))
        S2->SetPadding(FMargin(0.f, 0.f, 0.f, 16.f));
    if (UVerticalBoxSlot* S3 = Cast<UVerticalBoxSlot>(VBox->AddChild(MakeText(FText::FromString(TEXT("R3ALN3T.EXE   —   6th Gear Studios")), 20))))
        S3->SetPadding(FMargin(0.f, 0.f, 0.f, 0.f));
}

void UEngineSplashWidget::FinishSplash()
{
    if (bFinished) return;
    bFinished = true;

    if (IsInViewport())
    {
        RemoveFromParent();
    }
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
