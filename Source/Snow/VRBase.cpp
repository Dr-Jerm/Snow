// Fill out your copyright notice in the Description page of Project Settings.

#include "Snow.h"
#include "VRBase.h"
#include "UnrealNetwork.h"
//#include "SnowHTTP.h"
#include "SnowLogger.h"

/* VR Includes */
#include "HeadMountedDisplay.h"
#include "IMotionController.h"


// Sets default values
AVRBase::AVRBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->Customization.Init(-1, 5);
	this->headPositionVelocities.Init(FVector(0.f, 0.f, 0.f), velocityTicks);
	this->headRotationVelocities.Init(FVector(0.f, 0.f, 0.f), velocityTicks);
	this->leftPositionVelocities.Init(FVector(0.f, 0.f, 0.f), velocityTicks);
	this->leftRotationVelocities.Init(FVector(0.f, 0.f, 0.f), velocityTicks);
	this->rightPositionVelocities.Init(FVector(0.f, 0.f, 0.f), velocityTicks);
	this->rightRotationVelocities.Init(FVector(0.f, 0.f, 0.f), velocityTicks);
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

	FVector headPosDiff = vrState.headPosition - lastHeadPosition;
	headPositionVelocities.Insert(headPosDiff / DeltaTime, 0);
	headPositionVelocities.Pop();
	vrState.headPositionVelocity = this->getVectorArrayAverage(headPositionVelocities);
	lastHeadPosition = vrState.headPosition;

	//FRotator headRotDiff = vrState.headRotation - lastHeadRotation;
	//headRotationVelocities.Insert(headRotDiff / DeltaTime, 0);
	//headRotationVelocities.Pop();
	vrState.headAngularDiff = FQuat::Slerp(lastHeadRotation.Quaternion(), vrState.headRotation.Quaternion(), DeltaTime).Rotator();
	//FQuat(headRotDiff).Slerp()
	//vrState.headAngularDiff = this->getVectorArrayAverage(headRotationVelocities);
	lastHeadRotation = vrState.headRotation;

	FVector leftPosDiff = vrState.leftHandPosition - lastLeftPosition;
	leftPositionVelocities.Insert(leftPosDiff / DeltaTime, 0);
	leftPositionVelocities.Pop();
	leftHandVelocity = this->getVectorArrayAverage(leftPositionVelocities);
	vrState.leftHandPositionVelocity = leftHandVelocity;
	lastLeftPosition = vrState.leftHandPosition;

	//FVector leftRotDiff = vrState.leftHandRotation.Vector() - lastLeftRotation.Vector();
	//leftRotationVelocities.Insert(leftRotDiff / DeltaTime, 0);
	//leftRotationVelocities.Pop();
	//vrState.leftHandAngularDiff = this->getVectorArrayAverage(leftRotationVelocities);
	vrState.leftHandAngularDiff = FQuat::Slerp(vrState.leftHandRotation.Quaternion(), lastLeftRotation.Quaternion(), DeltaTime).Rotator();
	lastLeftRotation = vrState.leftHandRotation;

	FVector rightPosDiff = vrState.rightHandPosition - lastRightPosition;
	rightPositionVelocities.Insert(rightPosDiff / DeltaTime, 0);
	rightPositionVelocities.Pop();
	rightHandVelocity = this->getVectorArrayAverage(rightPositionVelocities);
	vrState.rightHandPositionVelocity = rightHandVelocity;
	lastRightPosition = vrState.rightHandPosition;

	//FVector rightRotDiff = vrState.rightHandRotation.Vector() - lastRightRotation.Vector();
	//rightRotationVelocities.Insert(rightRotDiff / DeltaTime, 0);
	//rightRotationVelocities.Pop();
	//vrState.rightHandAngularDiff = this->getVectorArrayAverage(rightRotationVelocities);
	vrState.rightHandAngularDiff = FQuat::Slerp(vrState.rightHandRotation.Quaternion(), lastRightRotation.Quaternion(), DeltaTime).Rotator();
	lastRightRotation = vrState.rightHandRotation;

	this->Server_UpdateServerWithVRState(vrState);
}

// Called to bind functionality to input
void AVRBase::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}


void AVRBase::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	DOREPLIFETIME(AVRBase, Customization);
	DOREPLIFETIME(AVRBase, vrStateReplicated);
}

void AVRBase::OnRep_Customization() {
	this->appearanceChange();
	//USnowHTTP::Instance()->MyHttpCall(NULL);
	//USnowHTTP::MyHttpCall();
}

void AVRBase::OnRep_VrStateReplicated() {
	ReplicatedThisTick = true;
}

void AVRBase::Server_UpdateServerWithVRState_Implementation(FVRState state)
{
	vrStateReplicated = state;
	ReplicatedThisTick = true;
	// Do something here that modifies game state.
}

bool AVRBase::Server_UpdateServerWithVRState_Validate(FVRState state)
{
	// Optionally validate the request and return false if the function should not be run.
	return true;
}

FVector AVRBase::getVectorArrayAverage(TArray<FVector> inputArray) {
	FVector sum = FVector(0.f, 0.f, 0.f);
	for (auto& vec : inputArray) {
		sum = sum + vec;
	}
	return sum / inputArray.Num();
}

FRotator AVRBase::getRotatorArrayAverage(TArray<FQuat> inputArray) {
	FQuat sum = FQuat(0.f, 0.f, 0.f, 0.f);
	for (auto& quat : inputArray) {
		sum = sum + quat;
	}
	return FQuat(sum / inputArray.Num()).Rotator();
}

