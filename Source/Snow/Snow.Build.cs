// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Snow : ModuleRules
{
	public Snow(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Sockets", "Networking" });

        /* HTTP Module */
        PublicDependencyModuleNames.AddRange(new string[] { "Http", "Json", "JsonUtilities" });

        /* Online Module */
        PublicDependencyModuleNames.AddRange(new string[] {
             "OnlineSubsystem",
             "OnlineSubsystemUtils"
         });

        //DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
        //DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");

        /* VR Module */
        PrivateDependencyModuleNames.AddRange(new string[] { "HeadMountedDisplay" });

        /* 3rd Party Plugins */
        PrivateDependencyModuleNames.AddRange(new string[] { "VaRestPlugin" });
        //PrivateDependencyModuleNames.AddRange(new string[] { "AdvancedSessions" });




        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");
        // if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
        // {
        //		if (UEBuildConfiguration.bCompileSteamOSS == true)
        //		{
        //			DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
        //		}
        // }
    }
}
