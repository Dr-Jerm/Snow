// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MotionControllerComponent.h"
#include "VRState.h"
#include "Core.h"
//#include "PawnAppearance.h"
#include "GameFramework/Pawn.h"
#include "VRBase.generated.h"

UCLASS()
class SNOW_API AVRBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVRBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	IHeadMountedDisplay* HMD = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VR)
	FVector leftHandVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VR)
	FVector rightHandVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VR)
	FVRState vrState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Replication)
	FVRState vrStateReplicated;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Replication)
	TArray<FVRState> vrStateBuffer;

	UFUNCTION(BlueprintImplementableEvent, Category = "Replication")
	void vrStateUpdate();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Replication)
	bool ReplicatedThisTick = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Replication)
	float lastReplicationDelta = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Customization, ReplicatedUsing = OnRep_Customization)
	TArray<int32> Customization;

	UFUNCTION(BlueprintImplementableEvent, Category = "Customization")
	void appearanceChange();
	
	UFUNCTION(Server, Unreliable, WithValidation)
	void Server_UpdateServerWithVRState(FVRState state);

	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_BroadcastVRState(FVRState state);

private:

	UFUNCTION()
	void OnRep_Customization();

	FVector getVectorArrayAverage(TArray<FVector>);
	FRotator getRotatorArrayAverage(TArray<FQuat>);

	int32 velocityTicks = 2;
	int32 replicatedBufferSize = 3;
	float lastReplicationTime = 0.f;

	FVector lastHeadPosition = FVector(0.f, 0.f, 0.f);
	FRotator lastHeadRotation = FRotator(0.f, 0.f, 0.f);
	FVector lastLeftPosition = FVector(0.f, 0.f, 0.f);
	FRotator lastLeftRotation = FRotator(0.f, 0.f, 0.f);
	FVector lastRightPosition = FVector(0.f, 0.f, 0.f);
	FRotator lastRightRotation = FRotator(0.f, 0.f, 0.f);
	TArray<FVector> headPositionVelocities;
	TArray<FVector> headRotationVelocities;
	TArray<FVector> leftPositionVelocities;
	TArray<FVector> leftRotationVelocities;
	TArray<FVector> rightPositionVelocities;
	TArray<FVector> rightRotationVelocities;

	UMotionControllerComponent* leftHand = nullptr;
	UMotionControllerComponent* rightHand = nullptr;
};

