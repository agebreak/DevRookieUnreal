// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectDRU : ModuleRules
{
	public ProjectDRU(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "UMG", "GameplayTasks" });

		// D8049 Error Fix Code. - Kim Hyeonwoo, 2021.07.19.
		// Âü°í : https://stackoverflow.com/questions/35262140/whats-the-cause-of-a-d8049-error-in-visual-studio
		bLegacyPublicIncludePaths = false;
    }
}
