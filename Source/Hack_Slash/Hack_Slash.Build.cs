// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Hack_Slash : ModuleRules
{
	public Hack_Slash(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule" });
    }
}
