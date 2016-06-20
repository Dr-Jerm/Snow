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

	HMD = (IHeadMountedDisplay*)(GEngine->HMDDevice.Get());

	//TArray<IMotionController*> controllers = (TArray<IMotionController*>)GEngine->MotionControllerDevices;
	

	/*IMotionController::GetControllerOrientationAndPosition*/

	//if (controllers.Num() > 0) {
	//	playerMotionControls = controllers[0];
	//}
}

// Called every frame
void AVRBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	// this value doesn't move after the player spawns. The HMD components go
	// off on their merry way from this point.
	FTransform localTransform = this->GetTransform();
	FVector localPosition = localTransform.GetLocation();

	HMD->GetBaseRotation();
	FQuat tempRotator;
	FVector tempPosition;
	HMD->GetCurrentOrientationAndPosition(tempRotator, tempPosition);
	vrState.headPosition = tempPosition;
	//vrState.headPosition = tempPosition + localPosition;
	vrState.headRotation = tempRotator.Rotator();

	//if (playerMotionControls == nullptr) {
	//	TArray<IMotionController*> controllers = (TArray<IMotionController*>)GEngine->MotionControllerDevices;
	//	if (controllers.Num() > 0) {
	//		playerMotionControls = controllers[0];
	//	}
	//	else {
	//		return;
	//	}
	//}



	//bool leftTrack = playerMotionControls->GetControllerOrientationAndPosition(0, EControllerHand::Left, vrState.leftHandRotation, tempLPosition);
	//bool rightTrack = playerMotionControls->GetControllerOrientationAndPosition(0, EControllerHand::Right, vrState.rightHandRotation, tempRPosition);

	FVector leftDiff = vrState.leftHandPosition - lastLeft;
	leftHandVelocity = leftDiff / DeltaTime;
	lastLeft = vrState.leftHandPosition;

	FVector rightDiff = vrState.rightHandPosition - lastRight;
	rightHandVelocity = rightDiff / DeltaTime;
	lastRight = vrState.rightHandPosition;

}

// Called to bind functionality to input
void AVRBase::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

