// Fill out your copyright notice in the Description page of Project Settings.

#include "Snow.h"
#include "SteamGameInstance.h"
#include "OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemImpl.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemUtilsModule.h"

USteamGameInstance::USteamGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	/** Bind function for CREATING a Session */
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &USteamGameInstance::OnCreateSessionComplete);
	OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &USteamGameInstance::OnStartOnlineGameComplete);
}

bool USteamGameInstance::HostDedicatedServer(FString level, FName sessionName) {

	// Get the Online Subsystem to work with
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();

	if (OnlineSub)
	{
		UWorld* World = GetWorld();
		IOnlineSessionPtr SessionInt = Online::GetSessionInterface(World);

		if (SessionInt.IsValid())
		{
			FOnlineSessionSettings Settings;
			Settings.NumPublicConnections = 6;
			Settings.NumPrivateConnections = 0;
			Settings.bShouldAdvertise = true;
			Settings.bAllowJoinInProgress = true;
			Settings.bAllowInvites = true;
			Settings.bIsLANMatch = false;
			Settings.bUsesPresence = false;
			Settings.bAllowJoinViaPresence = false;
			Settings.bIsDedicated = true;
			Settings.Set(SETTING_MAPNAME, level, EOnlineDataAdvertisementType::ViaOnlineService);
			Settings.Set(SETTING_CUSTOMSEARCHINT1, 0, EOnlineDataAdvertisementType::ViaOnlineService);

			UE_LOG(LogTemp, Log, TEXT("Creating Dedicated Session"));
			// Set the delegate to the Handle of the SessionInterface
			OnCreateSessionCompleteDelegateHandle = SessionInt->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);
			
			//HostDedicatedMapRequest(level);
			return SessionInt->CreateSession(0, sessionName, Settings);
		}
	}
	UE_LOG(LogTemp, Error, TEXT("Creating Dedicated Session Failed. OnlineSubsystem not valid."));
	return false;
}

void USteamGameInstance::StartDedicatedSession() {
	UWorld* World = GetWorld();
	IOnlineSessionPtr SessionInt = Online::GetSessionInterface(World);
	SessionInt->StartSession(GameSessionName);
	return;
}

void USteamGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Log, TEXT("OnCreateSessionComplete %s, %d"), *SessionName.ToString(), bWasSuccessful);

	// Get the OnlineSubsystem so we can get the Session Interface
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		// Get the Session Interface to call the StartSession function
		IOnlineSessionPtr SessionInt = OnlineSub->GetSessionInterface();

		if (SessionInt.IsValid())
		{
			// Clear the SessionComplete delegate handle, since we finished this call
			SessionInt->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
			if (bWasSuccessful)
			{
				// Set the StartSession delegate handle
				OnStartSessionCompleteDelegateHandle = SessionInt->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);

				// Our StartSessionComplete delegate should get called after this
				SessionInt->StartSession(SessionName);
			}
			else {
				UE_LOG(LogTemp, Error, TEXT("Creating Dedicated Session Failed. Creating Session was not successful."));
			}
		}
	}
}

void USteamGameInstance::OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Log, TEXT("OnStartSessionComplete %s, %d"), *SessionName.ToString(), bWasSuccessful);

	// Get the Online Subsystem so we can get the Session Interface
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		// Get the Session Interface to clear the Delegate
		IOnlineSessionPtr SessionInt = OnlineSub->GetSessionInterface();
		if (SessionInt.IsValid())
		{
			// Clear the delegate, since we are done with this call
			SessionInt->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);
		}
	}

	// If the start was successful, we can open a NewMap if we want. Make sure to use "listen" as a parameter!
	if (bWasSuccessful)
	{
		//FString map;
		//Settings->Get(SETTING_MAPNAME, *map);
		UGameplayStatics::OpenLevel(GetWorld(), "BRL_rag", true, "listen");
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Creating Dedicated Session Failed. Starting Session was not successful."));
	}
}
