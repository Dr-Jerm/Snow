//-------------------------------
// MyBlueprintFunctionLibrary.cpp
//-------------------------------

#include "Snow.h"
#include "KinematicsFunctionLibrary.h"

UKinematicsFunctionLibrary::UKinematicsFunctionLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}


FVector UKinematicsFunctionLibrary::KinematicsCalculatePosition(FVector initialPosition, FVector initialVelocity, FVector acceleration, float time)
{
	// Standard kinematics equation
	// ( (a0 / 2) * t^2 ) + (v0 * t) + d0 = d

	// Calculate acceleration component
	FVector distanceFromAcceleration = (acceleration / 2) * (time * time);

	// Calculate velocity component
	FVector distanceFromVelocity = initialVelocity * time;

	// Add all components together and return
	return distanceFromAcceleration + distanceFromVelocity + initialPosition;
}

float UKinematicsFunctionLibrary::KinematicsCalculateTime(FVector initialPosition, FVector initialVelocity, FVector acceleration, FVector position)
{
	// Quadratic formula to solve for time
	// t = ( -v0 +/- sqrt( v0^2 - 2*a*(d0-d) ) ) / a

	// Solve Discriminant
	FVector discriminant = initialVelocity*initialVelocity - (2 * acceleration * (initialPosition - position));

	
	discriminant.X = sqrt(discriminant.X);
	discriminant.Y = sqrt(discriminant.Y);
	discriminant.Z = sqrt(discriminant.Z);

	float time = ((-1 * initialVelocity - discriminant) / acceleration).Z;

	// We only care about the subtraction case of the quadratic (the largest solution to t=0 i.e. the end of the arc)
	return time;
}

FVector UKinematicsFunctionLibrary::KinematicsCalculateVelocity(FVector initialVelocity, FVector acceleration, float time) {
	return initialVelocity + acceleration * time;
}

FVector UKinematicsFunctionLibrary::KinematicsCalculateInitialVelocity(FVector initialPosition, FVector hitPosition, FVector acceleration, float hitTime) {
	return ((hitPosition - initialPosition) - ((hitTime * hitTime / 2) * acceleration)) / hitTime;
}