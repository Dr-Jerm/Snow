// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VR)
	FVector leftHandPosition;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VR)
	FRotator leftHandOrientation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VR)
	FVector rightHandPosition;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VR)
	FRotator rightHandOrientation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VR)
	FVector leftHandVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VR)
	FVector rightHandVelocity;

private:

	IMotionController* playerMotionControls;

	FVector lastLeft = FVector(0.f, 0.f, 0.f);
	FVector lastRight = FVector(0.f, 0.f, 0.f);
};
