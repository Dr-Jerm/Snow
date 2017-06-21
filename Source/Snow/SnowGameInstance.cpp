// Fill out your copyright notice in the Description page of Project Settings.

#include "Snow.h"
#include "SnowGameInstance.h"


USnowGameInstance::USnowGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	/** Bind function for CREATING a Session */
	//OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &USteamGameInstance::OnCreateSessionComplete);
	//OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &USteamGameInstance::OnStartOnlineGameComplete);
}

void USnowGameInstance::SelectBestSnowSession_Implementation(FBlueprintSessionResult &session) {
	FBlueprintSessionResult result;

	if (CachedSessions.Num() == 0) {
		session = result;
		return;
	}

	result = CachedSessions[0];

	session = result;
}

