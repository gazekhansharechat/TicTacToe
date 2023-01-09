// Fill out your copyright notice in the Description page of Project Settings.


#include "TTTSession.h"
#include "OnlineSubsystemSessionSettings.h"
#include "OnlineSubsystemUtils.h"
#include "Engine/World.h"

ATTTSession::ATTTSession()
{
	SessionName = FName("TTTSessionName");
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &ATTTSession::OnCreateSessionComplete);

}

void ATTTSession::RegisterServer()
{
	Super::RegisterServer();

	//Create a session
	UE_LOG(LogTemp, Warning, TEXT("In Game Session Dedicated Server Found !"));

	//Create Session on Server
	if (!bGameSessionCreated)
	{
		IOnlineSubsystem* OnlineSub = Online::GetSubsystem(GetWorld());

		if (OnlineSub)
		{
			IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();
			if (SessionInterface.IsValid())
			{

				if (SessionInterface->GetNumSessions() > 0)
					return;

				FOnlineSessionSettings* sessionSettings = new FOnlineSessionSettings();
				sessionSettings->bIsLANMatch = true;
				sessionSettings->bShouldAdvertise = true;
				sessionSettings->bIsDedicated = true;
				sessionSettings->bAllowInvites = true;
				sessionSettings->bUseLobbiesIfAvailable = true;
				sessionSettings->bUseLobbiesVoiceChatIfAvailable = true;
				sessionSettings->bAllowJoinInProgress = true;
				sessionSettings->bAllowJoinViaPresence = true;
				sessionSettings->bUsesPresence = true;
				sessionSettings->NumPrivateConnections = 10;
				sessionSettings->NumPublicConnections = 10;
				sessionSettings->Set(SETTING_MAPNAME, FString("ServerMap"), EOnlineDataAdvertisementType::ViaOnlineService);

				OnCreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

				if (SessionInterface->CreateSession(0, NAME_GameSession, *sessionSettings))
				{
					UE_LOG(LogTemp, Warning, TEXT("Creating Session Successfully triggered!"));
				}
			}
		}
	}
		/*UTTTGameInstance* instance = Cast<UTTTGameInstance>(GetGameInstance());

		check(instance)

			instance->OnStartDedicatedServer();*/
}

	void ATTTSession::OnCreateSessionComplete(FName SsName, bool bWasSuccessful)
	{
		const IOnlineSessionPtr sessionInterface = Online::GetSessionInterface(GetWorld());
		if (sessionInterface)
		{
			sessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
		}

		if (bWasSuccessful)
		{
			UE_LOG(LogTemp, Warning, TEXT("Called OnCreateSessionComplete"));
			bGameSessionCreated = true;
			//CurrentSessionType = SessionType::Created;
			//StartSession();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed  OnCreateSessionComplete"));
		}
	}


