// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AdvancedFriendsGameInstance.h"
#include "OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemImpl.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemUtilsModule.h"
#include "SnowGameInstance.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EOnlineStateEnum : uint8
{
	OS_Offline 		UMETA(DisplayName = "Offline"),
	OS_Searching 	UMETA(DisplayName = "Searching"),
	OS_Results	    UMETA(DisplayName = "Results"),
	OS_None_Found   UMETA(DisplayName = "None Found"),
	OS_Joining	    UMETA(DisplayName = "Joining"),
	OS_Connected	UMETA(DisplayName = "Connected"),
	OS_Hosting	    UMETA(DisplayName = "Hosting"),
	OS_Error	    UMETA(DisplayName = "Error"),
	OS_Unknown	    UMETA(DisplayName = "Unknown")
};

/**
 * 
 */
UCLASS()
class SNOW_API USnowGameInstance : public UAdvancedFriendsGameInstance
{
	GENERATED_BODY()
	
public:
	USnowGameInstance(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnlineSubsystem")
	TArray<FBlueprintSessionResult> CachedSessions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnlineSubsystem")
	FString ErrorMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnlineSubsystem")
	EOnlineStateEnum OnlineState = EOnlineStateEnum::OS_Offline;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "OnlineSubsystem")
	void SearchSessions(bool autoJoin);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "OnlineSubsystem")
	void HostSession(FName level);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "OnlineSubsystem")
	void JoinSession(FBlueprintSessionResult session);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "OnlineSubsystem")
	void LeaveSession(FName level);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "OnlineSubsystem")
	void SessionServerTravel(FName level);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "OnlineSubsystem")
	void SelectBestSession(FBlueprintSessionResult &session);
	

};
