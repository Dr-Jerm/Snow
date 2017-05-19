// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameLiftServerSDK.h"
#include "GameFramework/GameMode.h"
#include "SnowGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SNOW_API ASnowGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	ASnowGameMode(const FObjectInitializer& ObjectInitializer);

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Game)
	//int32 MaxPlayers = 1;

	virtual void HandleSeamlessTravelPlayer(AController *& C) override;

	FGameLiftServerSDKModule* gameLiftSdkModule;

	//int32 GetMaxPlayers();

	UFUNCTION(BlueprintImplementableEvent, Category = ServerTravel)
	void SeamlessTravelPlayer(AController* Controller);

	UFUNCTION(BlueprintCallable, Category = GameLift)
	void RegisterPlayer(const FString playerId);

	UFUNCTION(BlueprintCallable, Category = GameLift)
	void RemovePlayer(const FString playerId);
	
};
