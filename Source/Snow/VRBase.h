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
	FVector currentOriginPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VR)
	FRotator currentOriginRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VR)
	FVector leftHandVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VR)
	FVector rightHandVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VR)
	FVRState vrState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Customization, ReplicatedUsing = OnRep_Customization)
	TArray<int32> Customization;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Customization, ReplicatedUsing = OnRep_hatId)
	int32 hatId = -1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Customization, ReplicatedUsing = OnRep_goggleId)
	int32 goggleId = -1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Customization, ReplicatedUsing = OnRep_chinId)
	int32 chinId = -1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Customization, ReplicatedUsing = OnRep_gloveId)
	int32 gloveId = -1;

	UFUNCTION(BlueprintImplementableEvent, Category = "Customization")
	void appearanceChange();
	

private:

	UFUNCTION()
	void OnRep_Customization();

	UFUNCTION()
	void OnRep_hatId();
	UFUNCTION()
	void OnRep_goggleId();
	UFUNCTION()
	void OnRep_chinId();
	UFUNCTION()
	void OnRep_gloveId();

	//IMotionController* playerMotionControls;

	FVector lastLeft = FVector(0.f, 0.f, 0.f);
	FVector lastRight = FVector(0.f, 0.f, 0.f);

	UMotionControllerComponent* leftHand = nullptr;
	UMotionControllerComponent* rightHand = nullptr;
};

