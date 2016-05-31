#pragma once

#include "Snow.h"
#include "VRState.generated.h"

USTRUCT(BlueprintType)
struct FVRState
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Struct")
	FVector headPosition;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Struct")
	FRotator headRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Struct")
	FVector leftHandPosition;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Struct")
	FRotator leftHandRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Struct")
	FVector rightHandPosition;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Struct")
	FRotator rightHandRotation;

	//For GC
	void Destroy() {
	}

	//Constructor
	FVRState() {
	}
};
