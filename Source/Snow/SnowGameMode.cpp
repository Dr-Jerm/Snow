// Fill out your copyright notice in the Description page of Project Settings.

#include "Snow.h"
#include "OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemImpl.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemUtilsModule.h"
#include "SnowGameMode.h"


ASnowGameMode::ASnowGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	//Let's run this code only if GAMELIFT is enabled. Only with Server targets!
	#if WITH_GAMELIFT

		//Getting the module first.
		gameLiftSdkModule = &FModuleManager::LoadModuleChecked<FGameLiftServerSDKModule>(FName("GameLiftServerSDK"));

		//InitSDK establishes a local connection with GameLift's agent to enable further communication.
		gameLiftSdkModule->InitSDK();

		//When a game session is created, GameLift sends an activation request to the game server and passes along the game session object containing game properties and other settings.
		//Here is where a game server should take action based on the game session object.
		//Once the game server is ready to receive incoming player connections, it should invoke GameLiftServerAPI.ActivateGameSession()
		auto onGameSession = [=](Aws::GameLift::Server::Model::GameSession gameSession)
		{
			gameSession.SetMaximumPlayerSessionCount(6);
			gameLiftSdkModule->ActivateGameSession();
		};

		FProcessParameters* params = new FProcessParameters();
		params->OnStartGameSession.BindLambda(onGameSession);

		//OnProcessTerminate callback. GameLift invokes this callback before shutting down an instance hosting this game server.
		//It gives this game server a chance to save its state, communicate with services, etc., before being shut down.
		//In this case, we simply tell GameLift we are indeed going to shutdown.
		params->OnTerminate.BindLambda([=]() {gameLiftSdkModule->ProcessEnding(); });

		//This is the HealthCheck callback.
		//GameLift invokes this callback every 60 seconds or so.
		//Here, a game server might want to check the health of dependencies and such.
		//Simply return true if healthy, false otherwise.
		//The game server has 60 seconds to respond with its health status. GameLift defaults to 'false' if the game server doesn't respond in time.
		//In this case, we're always healthy!
		params->OnHealthCheck.BindLambda([]() {return true; });

		//This game server tells GameLift that it listens on port 7777 for incoming player connections.
		params->port = 7777;

		//Here, the game server tells GameLift what set of files to upload when the game session ends.
		//GameLift uploads everything specified here for the developers to fetch later.
		TArray<FString> logfiles;
		logfiles.Add(TEXT("aLogFile.txt"));
		params->logParameters = logfiles;

		//Calling ProcessReady tells GameLift this game server is ready to receive incoming game sessions!
		gameLiftSdkModule->ProcessReady(*params);
	#endif
}

void ASnowGameMode::HandleSeamlessTravelPlayer(AController *& Controller) {
	Super::HandleSeamlessTravelPlayer(Controller);
	SeamlessTravelPlayer(Controller);
}

void ASnowGameMode::RegisterPlayer(const FString playerId)
{
	#if WITH_GAMELIFT
		gameLiftSdkModule->AcceptPlayerSession(playerId);

		//TArray<AActor*> FoundPlayerStates;
		//UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerState::StaticClass(), FoundPlayerStates);

		//if (FoundPlayerStates.Num() >= 6) {
		//	gameLiftSdkModule->UpdatePlayerSessionCreationPolicy(EPlayerSessionCreationPolicy::DENY_ALL);
		//}
	#endif
}

void ASnowGameMode::RemovePlayer(const FString playerId)
{
	#if WITH_GAMELIFT
		gameLiftSdkModule->RemovePlayerSession(playerId);
		
		//TArray<AActor*> FoundPlayerStates;
		//UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerState::StaticClass(), FoundPlayerStates);

		//if (FoundPlayerStates.Num() < 6) {
		//	gameLiftSdkModule->UpdatePlayerSessionCreationPolicy(EPlayerSessionCreationPolicy::ACCEPT_ALL);
		//}
	#endif	
}

//int32 ASnowGameMode::GetMaxPlayers() {
//	return this->MaxPlayers;
//}

