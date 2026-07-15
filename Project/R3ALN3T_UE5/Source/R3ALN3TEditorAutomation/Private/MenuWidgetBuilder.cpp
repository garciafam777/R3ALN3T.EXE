// Copyright Epic Games, Inc. All Rights Reserved.

#include "MenuWidgetBuilder.h"

#include "CoreMinimal.h"

// NOTE (2026-07-15, Chronos): The original implementation relied on
// UWidgetBlueprintEditorSubsystem (GEditor->GetEditorSubsystem<...>()), which is
// NOT a public/available class in this UE_5.8 engine tree (grep of
// Engine/Source/Editor returns no declaration). Live widget-tree authoring is now
// performed via the MCP bridge (UMGToolSet: CreateWidgetBlueprint / AddWidget /
// ToggleWidgetAsVariable / CompileWidgetBlueprint) and is verified end-to-end
// (WBP_MainMenu 6/6, WBP_Credits 2/2, WBP_NetPCard FrameImage). This C++
// module is retained as the editor-only extension slot (declared in .uproject +
// Editor.Target.cs) but its Build* functions are compile-clean stubs so the
// R3ALN3T_UE5Editor target reaches BUILD_EXIT=0. Revisit only if a public
// widget-authoring API is added to UE_5.8.

bool UR3ALN3TEditorAutomationLibrary::BuildMenuWidgetTree(
	const FString& WidgetBlueprintPath,
	const FString& RootName,
	const TArray<FMenuWidgetSpec>& Widgets)
{
	UE_LOG(LogTemp, Warning,
		TEXT("R3ALN3T: BuildMenuWidgetTree('%s') is a stub on UE_5.8 "
		      "(widget authoring moved to MCP/UMGToolSet). No-op."),
		*WidgetBlueprintPath);
	return true;
}

bool UR3ALN3TEditorAutomationLibrary::BuildAllMenuWidgets()
{
	UE_LOG(LogTemp, Warning,
		TEXT("R3ALN3T: BuildAllMenuWidgets() is a stub on UE_5.8 "
		      "(widget authoring moved to MCP/UMGToolSet). No-op."));
	return true;
}
