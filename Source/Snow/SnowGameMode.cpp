// Fill out your copyright notice in the Description page of Project Settings.

#include "Snow.h"
#include "OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemImpl.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemUtilsModule.h"
#include "SnowGameMode.h"


void ASnowGameMode::HandleSeamlessTravelPlayer(AController *& Controller) {
	Super::HandleSeamlessTravelPlayer(Controller);
	SeamlessTravelPlayer(Controller);
}

