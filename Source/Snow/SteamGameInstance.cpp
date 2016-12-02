// Fill out your copyright notice in the Description page of Project Settings.

#include "Snow.h"
#include "SteamGameInstance.h"
#include "OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemImpl.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemUtilsModule.h"
#include "SnowGameMode.h"

USteamGameInstance::USteamGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	/** Bind function for CREATING a Session */
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &USteamGameInstance::OnCreateSessionComplete);
	OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &USteamGameInstance::OnStartOnlineGameComplete);
}

bool USteamGameInstance::HostDedicatedServer(FString level, FName sessionName, bool betaServer) {

	// Get the Online Subsystem to work with
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();

	if (OnlineSub)
	{
		UWorld* World = GetWorld();
		IOnlineSessionPtr SessionInt = Online::GetSessionInterface(World);

		if (SessionInt.IsValid())
		{
			//FOnlineSessionSettings Settings;
			ASnowGameMode* MyGM = Cast<ASnowGameMode>(GetWorld()->GetAuthGameMode());

			if (MyGM) {
				Settings = MakeShareable(new FOnlineSessionSettings());
				Settings->Set(SETTING_GAMEMODE, FString(*MyGM->GetName()), EOnlineDataAdvertisementType::ViaOnlineService);
				Settings->Set(SETTING_MAPNAME, GetWorld()->GetMapName(), EOnlineDataAdvertisementType::ViaOnlineService);
				Settings->Set(SETTING_MATCHING_HOPPER, FString("Deathmatch"), EOnlineDataAdvertisementType::DontAdvertise);
				Settings->Set(SETTING_MATCHING_TIMEOUT, 120.0f, EOnlineDataAdvertisementType::ViaOnlineService);
				Settings->Set(SETTING_SESSION_TEMPLATE_NAME, FString("GameSession"), EOnlineDataAdvertisementType::DontAdvertise);
				Settings->Set(SETTING_CUSTOM, betaServer ? FString("beta") : FString("default"), EOnlineDataAdvertisementType::ViaOnlineService);
				Settings->NumPublicConnections = this->MaxPlayers;
				Settings->NumPrivateConnections = 0;
				Settings->bShouldAdvertise = true;
				Settings->bAllowJoinInProgress = true;
				Settings->bAllowInvites = true;
				Settings->bIsLANMatch = false;
				Settings->bUsesPresence = false;
				Settings->bAllowJoinViaPresence = false;
				Settings->bIsDedicated = true;

				UE_LOG(LogTemp, Log, TEXT("Creating Dedicated Session"));
				// Set the delegate to the Handle of the SessionInterface
				OnCreateSessionCompleteDelegateHandle = SessionInt->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

				//HostDedicatedMapRequest(level);
				return SessionInt->CreateSession(0, sessionName, *Settings);
			}
		}
	}
	FString error = "Creating Dedicated Session Failed. OnlineSubsystem not valid.";
	UE_LOG(LogTemp, Error, TEXT("%s"), *error);
	this->HostDedicatedFailed(error);
	return false;
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
				FString error = "Creating Dedicated Session Failed. Creating Session was not successful.";
				UE_LOG(LogTemp, Error, TEXT("%s"), *error);
				this->HostDedicatedFailed(error);
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

	if (bWasSuccessful) {

		this->HostDedicatedSuccess();
		UGameplayStatics::OpenLevel(GetWorld(), "BRL_rag", true, "listen");
	}
	else {
		FString error = "Creating Dedicated Session Failed. Starting Session was not successful.";
		UE_LOG(LogTemp, Error, TEXT("%s"), *error);
		this->HostDedicatedFailed(error);
	}
}
