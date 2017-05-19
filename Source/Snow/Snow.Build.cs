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

        /* AWS GameLift */
        PublicDependencyModuleNames.AddRange(new string[] { "GameLiftServerSDK" });

        //DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
        //DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");

        /* VR Modules */
        //PrivateDependencyModuleNames.AddRange(new string[] { "HeadMountedDisplay" });
        PrivateDependencyModuleNames.AddRange(new string[] { "SteamVR", "HeadMountedDisplay" });

        /* 3rd Party Plugins */
        PrivateDependencyModuleNames.AddRange(new string[] { "VaRestPlugin" });
        PrivateDependencyModuleNames.AddRange(new string[] { "AdvancedSessions" });
        PrivateIncludePathModuleNames.AddRange(new string[] { "AdvancedSessions" });




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
