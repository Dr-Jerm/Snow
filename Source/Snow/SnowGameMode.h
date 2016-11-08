// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

	virtual void HandleSeamlessTravelPlayer(AController *& C) override;

	UFUNCTION(BlueprintImplementableEvent, Category = ServerTravel)
	void SeamlessTravelPlayer(AController* Controller);
	
};
