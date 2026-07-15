// CreditsWidget.h — CREDITS (the "last thing we missed").
// Self-contained C++ widget: renders the R3ALN3T.EXE credits as a scrolling
// panel using only UMG primitives (no external asset / editor dependency).
// Content ported from the provided credits.html (canon: Lifein6thgear / R&Y / AD3026).
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "CreditsWidget.generated.h"

UCLASS()
class R3ALN3T_UE5_API UCreditsWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    virtual void NativeConstruct() override;

    // Back button (BindWidget in Blueprint). Closes credits, returns to menu.
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UButton* BackButton;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UScrollBox* CreditsScroll;

protected:
    UFUNCTION() void OnBackClicked();

private:
    // Build the credit rows from the canon data below.
    void PopulateCredits();

    // ---- Credit data (ported from credits.html) ----
    struct FCreditLine { FString Role; FString Name; bool bLead; };
    static const TArray<FCreditLine>& GetCoreTeam();
    static const TArray<FString>& GetSpecialThanks();
    static const FString& GetPlayerMessage();
};
