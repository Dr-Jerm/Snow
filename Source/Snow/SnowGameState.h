// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "GameFramework/GameState.h"
#include "SnowGameState.generated.h"

USTRUCT(BlueprintType)
struct FYourDataRow
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2D Array")
	TArray<int32> Target;

	//or could be using a simple data type instead of a Data Unit Struct
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="2D Array")
	//TArray<FString> Cols;

	FYourDataRow() {}
};

USTRUCT(BlueprintType)
struct FYourDataArray
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2D Array")
	TArray<FYourDataRow> Source;

	FYourDataArray() {}
};


/**
 * 
 */
UCLASS()
class SNOW_API ASnowGameState : public AGameState
{
	GENERATED_BODY()
	
public:

	ASnowGameState();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Scores")
	TArray<int32> Players;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Scores")
	FYourDataArray PlayerScores = FYourDataArray();

	UFUNCTION(BlueprintCallable, Category = "Scores")
	void PlayerJoin(const int32 playerId, int32 &playerScoreIndex);

	UFUNCTION(BlueprintCallable, Category = "Scores")
	void PlayerLeave(const int32 playerId);

	UFUNCTION(BlueprintCallable, Category = "Scores")
	void ResetScore(const int32 playerId);

	UFUNCTION(BlueprintCallable, Category = "Scores")
	void GetScore(const int32 sourcePlayerId, const int32 targetPlayerId, int32 &score);

	UFUNCTION(BlueprintCallable, Category = "Scores")
	void IncrementScore(const int32 sourcePlayerId, const int32 targetPlayerId, int32 &score);


private:

	int32 GetPlayerIndex(int32 playerId);
	
	int32 maxPlayerCount = 12;
	
};


