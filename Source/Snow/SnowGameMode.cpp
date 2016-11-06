// Fill out your copyright notice in the Description page of Project Settings.

#include "Snow.h"
#include "OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemImpl.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemUtilsModule.h"
#include "SnowGameMode.h"


void ASnowGameMode::HandleSeamlessTravelPlayer(AController *& Controller) {
	Super::HandleSeamlessTravelPlayer(Controller);
	SeamlessTravelPlayer(Controller);
}

void ASnowGameMode::HostDedicatedServer(FString level) {
	UWorld* World = GetWorld();
	IOnlineSessionPtr SessionInt = Online::GetSessionInterface(World);

	FOnlineSessionSettings Settings;
	Settings.NumPublicConnections = 6;
	Settings.bShouldAdvertise = true;
	Settings.bAllowJoinInProgress = true;
	Settings.bAllowInvites = true;
	Settings.bIsLANMatch = false;
	Settings.bUsesPresence = false;
	Settings.bAllowJoinViaPresence = false;
	Settings.bIsDedicated = true;

	UE_LOG(LogTemp, Log, TEXT("Creating Dedicated Session"));
	SessionInt->CreateSession(0, GameSessionName, Settings);
	HostDedicatedMapRequest(level);
	return;
}

