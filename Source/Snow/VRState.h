#pragma once

#include "Snow.h"
#include "VRState.generated.h"

USTRUCT(BlueprintType)
struct FVRState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	FVector headPosition = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	FRotator headRotation = FRotator(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	FVector leftHandPosition = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	FRotator leftHandRotation = FRotator(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	FVector rightHandPosition = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	FRotator rightHandRotation = FRotator(0.0f, 0.0f, 0.0f);

	//For GC
	void Destroy() {
	}

	//Constructor
	FVRState() {
	}
};
