// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "ConfigLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UConfigLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UConfigLibrary(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure, Category = "ConfigLibrary")
	static void ReadConfigStringValue(const FString FileNameWithPath, const FString VariableName, FString &value);

	UFUNCTION(BlueprintPure, Category = "ConfigLibrary")
	static void ReadConfigBoolValue(const FString FileNameWithPath, const FString VariableName, bool &value);

	UFUNCTION(BlueprintPure, Category = "ConfigLibrary")
	static void ReadConfigFloatValue(const FString FileNameWithPath, const FString VariableName, float &value);

	UFUNCTION(BlueprintPure, Category = "ConfigLibrary")
	static void ReadConfigIntValue(const FString FileNameWithPath, const FString VariableName, int32 &value);
};
