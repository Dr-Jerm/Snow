// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "SnowGameInstance.h"
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
class SNOW_API USteamGameInstance : public USnowGameInstance
{
	GENERATED_BODY()
public:
	USteamGameInstance(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Game)
	int32 MaxPlayers = 6;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hosting")
	//FString localIp;

	//UFUNCTION(BlueprintImplementableEvent, Category = "OnlineSubsystem")
	//void SearchSessions(bool autoJoin);

	TSharedPtr<class FOnlineSessionSettings> Settings;

	UFUNCTION(BlueprintImplementableEvent, Category = "Hosting")
	void HostDedicatedSuccess();

	UFUNCTION(BlueprintImplementableEvent, Category = "Hosting")
	void HostDedicatedFailed(const FString &error);

	UFUNCTION(BlueprintCallable, Category = "Hosting")
	bool HostDedicatedServer(FString level, bool betaSever);


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

