// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Server)]
public class SnowServerTarget : TargetRules
{
	public SnowServerTarget(TargetInfo Target) : base(Target)
    {
		Type = TargetType.Server;
        ExtraModuleNames.Add("Snow");
        bUsesSteam = true;
    }
}
