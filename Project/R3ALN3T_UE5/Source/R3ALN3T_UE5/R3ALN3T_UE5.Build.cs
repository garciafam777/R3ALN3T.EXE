// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class R3ALN3T_UE5 : ModuleRules
{
	public R3ALN3T_UE5(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",
			"UMG", "Slate", "SlateCore", "Niagara", "CinematicCamera",
			"LevelSequence", "MovieScene", "MovieSceneTracks",
			"Json", "JsonUtilities", "HTTP",
			"MediaAssets", "MediaUtils", "AIModule",
			"DeveloperSettings", "RenderCore"
			});

		PrivateDependencyModuleNames.AddRange(new string[] { 
		});
	}
}
