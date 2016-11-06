// Fill out your copyright notice in the Description page of Project Settings.

#include "Snow.h"
#include "SteamGameInstance.h"
//#include "OnlineSubSystemHeader.h"

USteamGameInstance::USteamGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void USteamGameInstance::HostDedicatedServer(FString level) {
	//UWorld* World = GetWorld();
	//IOnlineSessionPtr SessionInt = Online::GetSessionInterface(World);

	//FOnlineSessionSettings Settings;
	//Settings.NumPublicConnections = 3;
	//Settings.bShouldAdvertise = true;
	//Settings.bAllowJoinInProgress = true;
	//Settings.bIsLANMatch = true;
	//Settings.bUsesPresence = true;
	//Settings.bAllowJoinViaPresence = true;

	//SessionInt->CreateSession(0, GameSessionName, Settings);
	//return;
}
