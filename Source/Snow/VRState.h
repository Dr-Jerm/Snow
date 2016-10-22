#pragma once

#include "Snow.h"
#include "VRState.generated.h"

USTRUCT(BlueprintType)
struct FVRState
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Head")
	FVector headPosition = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Head")
	FRotator headRotation = FRotator(0.0f, 0.0f, 0.0f);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Head")
	FVector headPositionVelocity = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Head")
	FRotator headRotationVelocity = FRotator(0.0f, 0.0f, 0.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Left")
	FVector leftHandPosition = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Left")
	FRotator leftHandRotation = FRotator(0.0f, 0.0f, 0.0f);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Left")
	FVector leftHandPositionVelocity = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Left")
	FRotator leftHandRotationVelocity = FRotator(0.0f, 0.0f, 0.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Right")
	FVector rightHandPosition = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Right")
	FRotator rightHandRotation = FRotator(0.0f, 0.0f, 0.0f);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Right")
	FVector rightHandPositionVelocity = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Right")
	FRotator rightHandRotationVelocity = FRotator(0.0f, 0.0f, 0.0f);

	//For GC
	void Destroy() {
	}

	//Constructor
	FVRState() {
	}
};
