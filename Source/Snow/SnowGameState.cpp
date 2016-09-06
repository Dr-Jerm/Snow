// Fill out your copyright notice in the Description page of Project Settings.

#include "Snow.h"
#include "SnowGameState.h"
#include "UnrealNetwork.h"


ASnowGameState::ASnowGameState()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Players.Init("", this->maxPlayerCount);
	this->PlayersLastActive.Init(-1, this->maxPlayerCount);

}

// Called when the game starts or when spawned
void ASnowGameState::BeginPlay()
{
	Super::BeginPlay();
	this->PlayerScores.Source.Init(FYourDataRow(), this->maxPlayerCount);
	for (int32 x = 0; x < this->maxPlayerCount; x++) {
		this->PlayerScores.Source[x].Target.Init(0, this->maxPlayerCount);
	}
}

// Called every frame
void ASnowGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority()) { // Ensure Role == ROLE_Authority
		for (int32 i = 0; i < this->maxPlayerCount; i++) {
			FString idInSlot = this->Players[i];
			if (idInSlot != "") {
				this->PlayersLastActive[i] = this->PlayersLastActive[i] + DeltaTime;
			}
		}
	}
}


void ASnowGameState::PlayerJoin(const FString playerId, int32 &playerScoreIndex) {
	for (int32 i = 0; i < this->maxPlayerCount; i++) {
		FString idInSlot = this->Players[i];
		if (idInSlot == "") {
			this->Players[i] = playerId;
			this->PlayersLastActive[i] = 0.f;
			playerScoreIndex = i;
			return;
		}
	}
}

void ASnowGameState::PlayerLeave(const FString playerId) {

	int32 index = this->GetPlayerIndex(playerId);
	if (index == -1) {
		UE_LOG(LogTemp, Error, TEXT("PlayerId not found."));
		return;
	}

	this->Players[index] = "";
			
	for (int32 x = 0; x < this->maxPlayerCount; x++) {
		for (int32 y = 0; y < this->maxPlayerCount; y++) {
			if (x == index || y == index) {
				this->PlayerScores.Source[x].Target[y] = 0;
			}
		}
	}

	return;
}

void ASnowGameState::ResetScore(const FString playerId) {

	int32 index = this->GetPlayerIndex(playerId);
	if (index == -1) {
		UE_LOG(LogTemp, Error, TEXT("PlayerId not found."));
		return;
	}

	for (int32 x = 0; x < this->maxPlayerCount; x++) {
		for (int32 y = 0; y < this->maxPlayerCount; y++) {
			if (x == index || y == index) {
				this->PlayerScores.Source[x].Target[y] = 0;
				this->PlayersLastActive[x] = 0.f;
				this->PlayersLastActive[y] = 0.f;
			}
		}
	}

	return;
}

void ASnowGameState::GetScore(const FString sourcePlayerId, const FString targetPlayerId, int32 &score) {
	int32 sourceIndex = this->GetPlayerIndex(sourcePlayerId);
	if (sourceIndex == -1) {
		UE_LOG(LogTemp, Error, TEXT("sourcePlayerId not found."));
		score = -1;
		return;
	}
	int32 targetIndex = this->GetPlayerIndex(targetPlayerId);
	if (targetIndex == -1) {
		UE_LOG(LogTemp, Error, TEXT("targetPlayerId not found."));
		score = -1;
		return;
	}

	int32 sourceTargetScore = this->PlayerScores.Source[sourceIndex].Target[targetIndex];
	int32 targetSourceScore = this->PlayerScores.Source[targetIndex].Target[sourceIndex];
	score = sourceTargetScore - targetSourceScore;
	return;
}

void ASnowGameState::IncrementScore(const FString sourcePlayerId, const FString targetPlayerId, int32 &score) {
	int32 sourceIndex = this->GetPlayerIndex(sourcePlayerId);
	if (sourceIndex == -1) {
		UE_LOG(LogTemp, Error, TEXT("sourcePlayerId not found."));
		score = -1;
		return;
	}
	int32 targetIndex = this->GetPlayerIndex(targetPlayerId);
	if (targetIndex == -1) {
		UE_LOG(LogTemp, Error, TEXT("targetPlayerId not found."));
		score = -1;
		return;
	}

	int32 newScore = this->PlayerScores.Source[sourceIndex].Target[targetIndex] + 1;
	this->PlayerScores.Source[sourceIndex].Target[targetIndex] = newScore;
	score = newScore;
	this->PlayersLastActive[sourceIndex] = 0.f;
	this->PlayersLastActive[targetIndex] = 0.f;

	return;
}

int32 ASnowGameState::GetPlayerIndex(FString playerId) {
	for (int32 i = 0; i < this->maxPlayerCount; i++) {
		FString idInSlot = this->Players[i];
		if (idInSlot == playerId) {
			return i;
		}
	}
	return -1;
}

void ASnowGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASnowGameState, Players);
	DOREPLIFETIME(ASnowGameState, PlayerScores);
}


