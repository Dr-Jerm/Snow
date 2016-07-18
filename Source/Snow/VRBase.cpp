// Fill out your copyright notice in the Description page of Project Settings.

#include "Snow.h"
#include "VRBase.h"
#include "UnrealNetwork.h"

/* VR Includes */
#include "HeadMountedDisplay.h"
#include "IMotionController.h"


// Sets default values
AVRBase::AVRBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->Customization.Init(-1, 5);
	bReplicates = true;
}

// Called when the game starts or when spawned
void AVRBase::BeginPlay()
{
	Super::BeginPlay();

	HMD = (IHeadMountedDisplay*)(GEngine->HMDDevice.Get());
	//GetDefaultSubobjectByName<UMotionControllerComponent>(TEXT("LeftHand"));
	//leftHand->Hand = EControllerHand::Left;


	//TArray<IMotionController*> controllers = (TArray<IMotionController*>)GEngine->MotionControllerDevices;
	

	/*IMotionController::GetControllerOrientationAndPosition*/

	//if (controllers.Num() > 0) {
	//	playerMotionControls = controllers[0];
	//}

	TArray<UMotionControllerComponent*> comps;

	this->GetComponents(comps);
	for (UMotionControllerComponent* motionController : comps)
	{
		if (motionController->Hand == EControllerHand::Left) {
			leftHand = motionController;
		}
		else if (motionController->Hand == EControllerHand::Right) {
			rightHand = motionController;
		}
	}
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

	if (leftHand != nullptr) {
		FTransform lTrans = leftHand->GetRelativeTransform();
		FVector leftHandPosition = lTrans.GetTranslation();
		FRotator leftHandRotation = lTrans.GetRotation().Rotator();
		vrState.leftHandPosition = leftHandPosition;
		vrState.leftHandRotation = leftHandRotation;
	}
	if (rightHand != nullptr) {
		FTransform rTrans = rightHand->GetRelativeTransform();
		FVector rightHandPosition = rTrans.GetTranslation();
		FRotator rightHandRotation = rTrans.GetRotation().Rotator();
		vrState.rightHandPosition = rightHandPosition;
		vrState.rightHandRotation = rightHandRotation;
	}

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


void AVRBase::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	DOREPLIFETIME(AVRBase, Customization);
}

void AVRBase::OnRep_Customization() {
	this->appearanceChange();
}

