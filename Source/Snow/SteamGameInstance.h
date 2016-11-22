// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "AdvancedFriendsGameInstance.h"
#include "OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemImpl.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemUtilsModule.h"
#include "SteamGameInstance.generated.h"

///* Delegate called when session created */
//FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
///* Delegate called when session started */
//FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;
//
///** Handles to registered delegates for creating/starting a session */
//FDelegateHandle OnCreateSessionCompleteDelegateHandle;
//FDelegateHandle OnStartSessionCompleteDelegateHandle;

/**
 * 
 */
UCLASS()
class SNOW_API USteamGameInstance : public UAdvancedFriendsGameInstance
{
	GENERATED_BODY()
public:
	USteamGameInstance(const FObjectInitializer& ObjectInitializer);

	//TSharedPtr<class FOnlineSessionSettings> Settings;

	UFUNCTION(BlueprintImplementableEvent, Category = "Hosting")
	void HostDedicatedMapRequest(const FString &level);

	UFUNCTION(BlueprintCallable, Category = "Hosting")
	bool HostDedicatedServer(FString level, FName sessionName);

	UFUNCTION(BlueprintCallable, Category = "Hosting")
	void StartDedicatedSession();

	/**
	*	Function fired when a session create request has completed
	*
	*	@param SessionName the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	/**
	*	Function fired when a session start request has completed
	*
	*	@param SessionName the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);

private:

	/* Delegate called when session created */
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	/* Delegate called when session started */
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

	/** Handles to registered delegates for creating/starting a session */
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;
};

