// Fill out your copyright notice in the Description page of Project Settings.

#include "Snow.h"
#include "VRBase.h"
#include "UnrealNetwork.h"
//#include "SnowHTTP.h"

/* VR Includes */
#include "HeadMountedDisplay.h"
#include "IMotionController.h"


// Sets default values
AVRBase::AVRBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->Customization.Init(-1, 5);
	this->leftVelocities.Init(FVector(0.f, 0.f, 0.f), 2);
	this->rightVelocities.Init(FVector(0.f, 0.f, 0.f), 2);
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

	if (HMD == nullptr) {
		return;
	}
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
	leftVelocities.Insert(leftDiff / DeltaTime, 0);
	leftVelocities.Pop();
	leftHandVelocity = this->getArrayAverage(leftVelocities);
	lastLeft = vrState.leftHandPosition;

	FVector rightDiff = vrState.rightHandPosition - lastRight;
	rightVelocities.Insert(rightDiff / DeltaTime, 0);
	rightVelocities.Pop();
	rightHandVelocity = this->getArrayAverage(rightVelocities);
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
	//USnowHTTP::Instance()->MyHttpCall(NULL);
	//USnowHTTP::MyHttpCall();
}

FVector AVRBase::getArrayAverage(TArray<FVector> inputArray) {
	FVector sum = FVector(0.f, 0.f, 0.f);
	for (auto& vec : inputArray) {
		sum = sum + vec;
	}
	return sum / inputArray.Num();
}

