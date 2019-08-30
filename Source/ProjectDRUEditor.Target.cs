// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectDRUEditorTarget : TargetRules
{
	public ProjectDRUEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
        //ExtraModuleNames.Add("ProjectDRU", "ProjectDRUSetting");
        ExtraModuleNames.AddRange(new string[] { "ProjectDRU", "ProjectDRUSetting"});
	}
}
