// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemImpl.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemUtilsModule.h"
#include "SnowGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SNOW_API ASnowGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	virtual void HandleSeamlessTravelPlayer(AController *& C) override;

	UFUNCTION(BlueprintImplementableEvent, Category = ServerTravel)
	void SeamlessTravelPlayer(AController* Controller);

	UFUNCTION(BlueprintImplementableEvent, Category = "Hosting")
	void HostDedicatedMapRequest(const FString &level);
	
	UFUNCTION(BlueprintCallable, Category = "Hosting")
	void HostDedicatedServer(FString level);
	
};
