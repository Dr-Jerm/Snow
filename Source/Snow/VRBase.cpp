// Fill out your copyright notice in the Description page of Project Settings.

#include "Snow.h"
#include "VRBase.h"

/* VR Includes */
#include "HeadMountedDisplay.h"
#include "IMotionController.h"


// Sets default values
AVRBase::AVRBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVRBase::BeginPlay()
{
	Super::BeginPlay();

	TArray<IMotionController*> controllers = (TArray<IMotionController*>)GEngine->MotionControllerDevices;
	playerMotionControls = controllers[0];
	
}

// Called every frame
void AVRBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	bool leftTrack = playerMotionControls->GetControllerOrientationAndPosition(0, EControllerHand::Left, leftHandOrientation, leftHandPosition);
	bool rightTrack = playerMotionControls->GetControllerOrientationAndPosition(0, EControllerHand::Right, rightHandOrientation, rightHandPosition);

	if (leftTrack) {
		FVector leftDiff = leftHandPosition - lastLeft;
		leftHandVelocity = leftDiff / DeltaTime;
		lastLeft = leftHandPosition;
	}
	if (rightTrack) {
		FVector rightDiff = rightHandPosition - lastRight;
		rightHandVelocity = rightDiff / DeltaTime;
		lastRight = rightHandPosition;
	}
}

// Called to bind functionality to input
void AVRBase::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

