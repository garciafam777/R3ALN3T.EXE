// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class R3ALN3TEditorAutomation : ModuleRules
{
	public R3ALN3TEditorAutomation(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"UMG",
			"Slate",
			"SlateCore",
			"Blutility"
		});

		// Editor-only dependencies: this module is only compiled for editor targets.
		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(new string[]
			{
				"UMGEditor",
				"UnrealEd",
				"Kismet",
				"EditorScriptingUtilities"
			});
		}
	}
}
