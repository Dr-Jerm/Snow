// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "SteamGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SNOW_API USteamGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	USteamGameInstance(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Hosting")
	void HostDedicatedServer(FString level);
};

