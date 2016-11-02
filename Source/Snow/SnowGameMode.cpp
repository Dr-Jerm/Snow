// Fill out your copyright notice in the Description page of Project Settings.

#include "Snow.h"
#include "SnowGameMode.h"


void ASnowGameMode::HandleSeamlessTravelPlayer(AController *& Controller) {
	Super::HandleSeamlessTravelPlayer(Controller);
	SeamlessTravelPlayer(Controller);
}

