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
	this->vrStateBuffer.Init(FVRState(), this->replicatedBufferSize);
	bReplicates = true;
}

// Called when the game starts or when spawned
void AVRBase::BeginPlay()
{
	Super::BeginPlay();

	HMD = (IHeadMountedDisplay*)(GEngine->HMDDevice.Get());

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
	if (IsLocallyControlled()) {
		//Client version of the pawn

		// this value doesn't move after the player spawns. The HMD components go
		// off on their merry way from this point.
		FTransform localTransform = this->GetTransform();
		FVector localPosition = localTransform.GetLocation();

		HMD->GetBaseRotation();
		FQuat tempRotator;
		FVector tempPosition;
		HMD->GetCurrentOrientationAndPosition(tempRotator, tempPosition);
		vrState.headPosition = tempPosition;
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

		FRotator headDelta = vrState.headRotation - lastHeadRotation;
		vrState.headAngularDiff = (headDelta.Quaternion() / DeltaTime).Rotator();
		lastHeadRotation = vrState.headRotation;

		FVector leftPosDiff = vrState.leftHandPosition - lastLeftPosition;
		leftPositionVelocities.Insert(leftPosDiff / DeltaTime, 0);
		leftPositionVelocities.Pop();
		leftHandVelocity = this->getVectorArrayAverage(leftPositionVelocities);
		vrState.leftHandPositionVelocity = leftHandVelocity;
		lastLeftPosition = vrState.leftHandPosition;

		FRotator leftDelta = vrState.leftHandRotation - lastLeftRotation;
		vrState.leftHandAngularDiff = (leftDelta.Quaternion() / DeltaTime).Rotator();
		lastLeftRotation = vrState.leftHandRotation;

		FVector rightPosDiff = vrState.rightHandPosition - lastRightPosition;
		rightPositionVelocities.Insert(rightPosDiff / DeltaTime, 0);
		rightPositionVelocities.Pop();
		rightHandVelocity = this->getVectorArrayAverage(rightPositionVelocities);
		vrState.rightHandPositionVelocity = rightHandVelocity;
		lastRightPosition = vrState.rightHandPosition;

		FRotator rightDelta = vrState.rightHandRotation - lastRightRotation;
		vrState.rightHandAngularDiff = (rightDelta.Quaternion() / DeltaTime).Rotator();
		lastRightRotation = vrState.rightHandRotation;

		this->Server_UpdateServerWithVRState(vrState);
	}
}

// Called to bind functionality to input
void AVRBase::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}


void AVRBase::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	DOREPLIFETIME(AVRBase, Customization);
	//DOREPLIFETIME(AVRBase, vrStateReplicated);
}

void AVRBase::OnRep_Customization() {
	this->appearanceChange();
}

void AVRBase::Server_UpdateServerWithVRState_Implementation(FVRState state)
{
	this->Multicast_BroadcastVRState(state);
}
void AVRBase::Multicast_BroadcastVRState_Implementation(FVRState state)
{
	float realtimeSeconds = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	this->lastReplicationDelta = realtimeSeconds - this->lastReplicationTime;
	this->vrStateReplicated = state;
	this->ReplicatedThisTick = true;
	this->vrStateBuffer.Insert(state, 0);
	this->vrStateBuffer.Pop();
	this->vrStateUpdate();
	this->lastReplicationTime = realtimeSeconds;
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

