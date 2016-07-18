// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ECustomizationEnum : uint8
{
	CE_Base    = 0	UMETA(DisplayName = "Base"),
	CE_Hat     = 1	UMETA(DisplayName = "Hat"),
	CE_Goggles = 2	UMETA(DisplayName = "Goggles"),
	CE_Chin    = 3  UMETA(DisplayName = "Chin"),
	CE_Gloves  = 4  UMETA(DisplayName = "Gloves")
};

