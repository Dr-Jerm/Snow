// Fill out your copyright notice in the Description page of Project Settings.

#include "Snow.h"
#include "SnowGameState.h"
#include "UnrealNetwork.h"


ASnowGameState::ASnowGameState()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASnowGameState::BeginPlay()
{
	Super::BeginPlay();

	for (int32 x = 0; x < this->playerCount; x++) {
		for (int32 y = 0; y < this->playerCount; y++) {
			this->PlayerScores.Source[x].Target[y] = 0;
		}
		this->Players[x] = -1;
	}
}

// Called every frame
void ASnowGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ASnowGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	DOREPLIFETIME(ASnowGameState, Players);
	DOREPLIFETIME(ASnowGameState, PlayerScores);
	//DOREPLIFETIME(ASnowGameState, goggleId);
	//DOREPLIFETIME(ASnowGameState, chinId);
	//DOREPLIFETIME(ASnowGameState, gloveId);
}

