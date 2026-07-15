// CreditsWidget.cpp — CREDITS implementation.
#include "CreditsWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include "Components/Border.h"

namespace
{
    // Canonical credits (ported verbatim-role from credits.html).
    TArray<UCreditsWidget::FCreditLine> GCoreTeam = {
        { TEXT("Produced by"),     TEXT("Richard Garcia-Nieves"), true  },
        { TEXT("Co-Producer"),     TEXT("Chronos"),               false },
        { TEXT("Development"),     TEXT("Nyx"),                   false },
        { TEXT("Designs"),         TEXT("Echo"),                  false },
        { TEXT("Cyber-Integrator"),TEXT("Joker"),                 false },
    };
    TArray<FString> GSpecialThanks = {
        TEXT("The Makers of the Bible"),
        TEXT("Lifein6thgear Studios"),
        TEXT("R&Y Productions"),
    };
    FString GPlayerMessage = TEXT("And to every player who jacked in, ran the grid, and made it their own —");
    FString GStudioName    = TEXT("LIFEIN6THGEAR STUDIOS");
    FString GCopyright     = TEXT("\u00A9 AD3026 R&Y Productions \u00B7 All Rights Reserved");
}

const TArray<UCreditsWidget::FCreditLine>& UCreditsWidget::GetCoreTeam()    { return GCoreTeam; }
const TArray<FString>&                     UCreditsWidget::GetSpecialThanks(){ return GSpecialThanks; }
const FString&                            UCreditsWidget::GetPlayerMessage() { return GPlayerMessage; }

void UCreditsWidget::NativeConstruct()
{
    Super::NativeConstruct();
    if (BackButton) BackButton->OnClicked.AddDynamic(this, &UCreditsWidget::OnBackClicked);
    PopulateCredits();
}

void UCreditsWidget::OnBackClicked()
{
    RemoveFromParent();
}

void UCreditsWidget::PopulateCredits()
{
    if (!CreditsScroll) return;

    auto AddText = [&](const FString& InText, bool bLead, const FString& Role)
    {
        UVerticalBox* Row = NewObject<UVerticalBox>(this);
        if (!Role.IsEmpty())
        {
            UTextBlock* RoleT = NewObject<UTextBlock>(this);
            RoleT->SetText(FText::FromString(Role));
            RoleT->SetJustification(ETextJustify::Center);
            Row->AddChild(RoleT);
        }
        UTextBlock* NameT = NewObject<UTextBlock>(this);
        NameT->SetText(FText::FromString(InText));
        NameT->SetJustification(ETextJustify::Center);
        // Lead gets a larger size; UMG honors SetFont via Slate.
        FSlateFontInfo Font = NameT->GetFont();
        Font.Size = bLead ? 28 : 20;
        NameT->SetFont(Font);
        Row->AddChild(NameT);

        USizeBox* Spacer = NewObject<USizeBox>(this);
        Spacer->SetHeightOverride(40.f);
        Row->AddChild(Spacer);

        CreditsScroll->AddChild(Row);
    };

    // Title
    UTextBlock* Title = NewObject<UTextBlock>(this);
    Title->SetText(FText::FromString(TEXT("R3ALN3T.EXE")));
    Title->SetJustification(ETextJustify::Center);
    FSlateFontInfo TitleFont = Title->GetFont(); TitleFont.Size = 40; Title->SetFont(TitleFont);
    CreditsScroll->AddChild(Title);

    UTextBlock* Sub = NewObject<UTextBlock>(this);
    Sub->SetText(FText::FromString(TEXT("A LIFEIN6THGEAR STUDIOS PRODUCTION")));
    Sub->SetJustification(ETextJustify::Center);
    CreditsScroll->AddChild(Sub);

    UTextBlock* Year = NewObject<UTextBlock>(this);
    Year->SetText(FText::FromString(TEXT("// AD3026 //")));
    Year->SetJustification(ETextJustify::Center);
    CreditsScroll->AddChild(Year);

    // Core team
    for (const FCreditLine& C : GetCoreTeam())
        AddText(C.Name, C.bLead, C.Role);

    // Special thanks
    for (const FString& T : GetSpecialThanks())
        AddText(T, false, TEXT("Special Thanks"));

    // Player message
    AddText(GetPlayerMessage(), false, TEXT("Thank You"));

    // Studio footer
    UTextBlock* Studio = NewObject<UTextBlock>(this);
    Studio->SetText(FText::FromString(GStudioName));
    Studio->SetJustification(ETextJustify::Center);
    CreditsScroll->AddChild(Studio);

    UTextBlock* Copy = NewObject<UTextBlock>(this);
    Copy->SetText(FText::FromString(GCopyright));
    Copy->SetJustification(ETextJustify::Center);
    CreditsScroll->AddChild(Copy);
}
