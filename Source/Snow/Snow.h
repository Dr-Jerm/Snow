// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ECustomizationEnum : uint8
{
	CE_Base    = 0	UMETA(DisplayName = "Base"),
	CE_Gloves  = 1  UMETA(DisplayName = "Gloves"),
	CE_Hat     = 2	UMETA(DisplayName = "Hat"),
	CE_Eyes    = 3	UMETA(DisplayName = "Eyes"),
	CE_Chin    = 4  UMETA(DisplayName = "Chin")
	
};

