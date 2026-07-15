// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class R3ALN3T_UE5EditorTarget : TargetRules
{
	public R3ALN3T_UE5EditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V7;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8;
		ExtraModuleNames.Add("R3ALN3T_UE5");
		ExtraModuleNames.Add("R3ALN3TEditorAutomation");
	}
}
