// Fill out your copyright notice in the Description page of Project Settings.

#include "Snow.h"
#include "SnowPlayerState.h"
#include "UnrealNetwork.h"


ASnowPlayerState::ASnowPlayerState()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASnowPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASnowPlayerState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ASnowPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASnowPlayerState, ScoreIndex);
}



