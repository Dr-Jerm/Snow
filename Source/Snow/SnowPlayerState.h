// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "SnowPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SNOW_API ASnowPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	ASnowPlayerState();
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Scores")
	int32 ScoreIndex = -1;
	
};
