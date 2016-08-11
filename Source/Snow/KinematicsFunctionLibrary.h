#pragma once

#include "KinematicsFunctionLibrary.generated.h"

UCLASS()
class UKinematicsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UKinematicsFunctionLibrary(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure, Category = "Kinematics")
	static FVector KinematicsCalculatePosition(FVector initial_position, FVector initial_velocity, FVector acceleration, float time);

	UFUNCTION(BlueprintPure, Category = "Kinematics")
	static float KinematicsCalculateTime(FVector initialPosition, FVector initialVelocity, FVector acceleration, FVector position);

	UFUNCTION(BlueprintPure, Category = "Kinematics")
	static FVector KinematicsCalculateVelocity(FVector initialVelocity, FVector acceleration, float time);
};
