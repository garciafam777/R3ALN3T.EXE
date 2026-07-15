// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
// Forward-declare UWidget: the only use is TSubclassOf<UWidget> in the struct below.
// Avoids pulling UMG/Components/Widget.h (whose include alias is unreliable under
// this module's PCH settings on UE_5.8) while keeping the public API intact.
class UWidget;
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MenuWidgetBuilder.generated.h"

/**
 * Specifies one widget to add to a WidgetBlueprint's tree.
 * Name must match the C++ BindWidget declaration exactly.
 */
USTRUCT(BlueprintType)
struct FMenuWidgetSpec
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "R3ALN3T")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "R3ALN3T")
	TSubclassOf<UWidget> WidgetClass;
};

UCLASS()
class UR3ALN3TEditorAutomationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Author the widget tree of a WidgetBlueprint from C++ (where WidgetTree is
	 * fully accessible). Ensures a root CanvasPanel, then adds each named widget,
	 * parents it to the root, compiles and saves the blueprint.
	 * Returns true if the blueprint was loaded and processed.
	 */
	UFUNCTION(BlueprintCallable, Category = "R3ALN3T|Editor Automation", meta = (DevelopmentOnly))
	static bool BuildMenuWidgetTree(const FString& WidgetBlueprintPath, const FString& RootName, const TArray<FMenuWidgetSpec>& Widgets);

	/** Populates WBP_MainMenu (6 controls) and WBP_Credits (2 controls). */
	UFUNCTION(BlueprintCallable, Category = "R3ALN3T|Editor Automation", meta = (DevelopmentOnly))
	static bool BuildAllMenuWidgets();
};
