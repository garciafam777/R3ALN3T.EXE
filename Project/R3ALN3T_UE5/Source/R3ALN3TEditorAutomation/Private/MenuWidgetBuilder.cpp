// Copyright Epic Games, Inc. All Rights Reserved.

#include "MenuWidgetBuilder.h"

#include "WidgetBlueprint.h"
#include "WidgetTree.h"
#include "Components/PanelWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "WidgetBlueprintEditorSubsystem.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "EditorAssetLibrary.h"
#include "UnrealEd.h"

static FMenuWidgetSpec MakeSpec(const TCHAR* Name, TSubclassOf<UWidget> Cls)
{
	FMenuWidgetSpec Spec;
	Spec.Name = Name;
	Spec.WidgetClass = Cls;
	return Spec;
}

bool UR3ALN3TEditorAutomationLibrary::BuildMenuWidgetTree(
	const FString& WidgetBlueprintPath,
	const FString& RootName,
	const TArray<FMenuWidgetSpec>& Widgets)
{
	UWidgetBlueprint* WBP = LoadObject<UWidgetBlueprint>(nullptr, *WidgetBlueprintPath);
	if (!WBP || !WBP->WidgetTree)
	{
		UE_LOG(LogTemp, Error, TEXT("R3ALN3T: could not load WidgetBlueprint at %s"), *WidgetBlueprintPath);
		return false;
	}

	UWidgetBlueprintEditorSubsystem* Subsys = GEditor->GetEditorSubsystem<UWidgetBlueprintEditorSubsystem>();
	if (!Subsys)
	{
		UE_LOG(LogTemp, Error, TEXT("R3ALN3T: WidgetBlueprintEditorSubsystem unavailable"));
		return false;
	}

	UWidgetTree* Tree = WBP->WidgetTree;

	// Ensure a root CanvasPanel (first widget in an empty tree becomes the root).
	UPanelWidget* RootPanel = Cast<UPanelWidget>(Tree->RootWidget);
	if (!RootPanel)
	{
		UWidget* RootWidget = Subsys->CreateWidget(WBP, UCanvasPanel::StaticClass(), FName(*RootName));
		if (RootWidget)
		{
			Tree->RootWidget = RootWidget;
			RootPanel = Cast<UPanelWidget>(RootWidget);
		}
	}

	int32 Added = 0;
	for (const FMenuWidgetSpec& Spec : Widgets)
	{
		if (Spec.Name.IsEmpty() || !Spec.WidgetClass)
		{
			continue;
		}
		const FName WidgetName(*Spec.Name);
		if (Tree->FindWidget(WidgetName))
		{
			UE_LOG(LogTemp, Warning, TEXT("R3ALN3T: skip existing widget %s"), *Spec.Name);
			continue;
		}
		UWidget* NewWidget = Subsys->CreateWidget(WBP, Spec.WidgetClass, WidgetName);
		if (NewWidget && RootPanel)
		{
			RootPanel->AddChild(NewWidget);
			++Added;
			UE_LOG(LogTemp, Log, TEXT("R3ALN3T: added %s"), *Spec.Name);
		}
	}

	FBlueprintEditorUtils::MarkBlueprintAsModified(WBP);
	FKismetEditorUtilities::CompileBlueprint(WBP);
	UEditorAssetLibrary::SaveLoadedAsset(WBP, false);

	UE_LOG(LogTemp, Log, TEXT("R3ALN3T: BuildMenuWidgetTree(%s) done, added %d"), *WidgetBlueprintPath, Added);
	return true;
}

bool UR3ALN3TEditorAutomationLibrary::BuildAllMenuWidgets()
{
	TArray<FMenuWidgetSpec> MenuWidgets;
	MenuWidgets.Add(MakeSpec(TEXT("NewGameButton"), UButton::StaticClass()));
	MenuWidgets.Add(MakeSpec(TEXT("ContinueButton"), UButton::StaticClass()));
	MenuWidgets.Add(MakeSpec(TEXT("QuitButton"), UButton::StaticClass()));
	MenuWidgets.Add(MakeSpec(TEXT("CreditsButton"), UButton::StaticClass()));
	MenuWidgets.Add(MakeSpec(TEXT("TitleText"), UTextBlock::StaticClass()));
	MenuWidgets.Add(MakeSpec(TEXT("BackgroundImage"), UImage::StaticClass()));

	const bool bMenu = BuildMenuWidgetTree(
		TEXT("/Game/UI/Menu/WBP_MainMenu.WBP_MainMenu"),
		TEXT("RootCanvas"),
		MenuWidgets);

	TArray<FMenuWidgetSpec> CreditsWidgets;
	CreditsWidgets.Add(MakeSpec(TEXT("CreditsScroll"), UScrollBox::StaticClass()));
	CreditsWidgets.Add(MakeSpec(TEXT("BackButton"), UButton::StaticClass()));

	const bool bCredits = BuildMenuWidgetTree(
		TEXT("/Game/WBP_Credits.WBP_Credits"),
		TEXT("RootCanvas"),
		CreditsWidgets);

	UE_LOG(LogTemp, Log, TEXT("R3ALN3T: BuildAllMenuWidgets menu=%d credits=%d"), bMenu, bCredits);
	return bMenu && bCredits;
}
