// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Online.h"
#include "GameFramework/GameSession.h"
#include "TTTSession.generated.h"
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCSOnStartSessionComplete, bool, Successful);
UCLASS()
class TICTACTOE_API ATTTSession : public AGameSession
{
	GENERATED_BODY()

	ATTTSession();

	bool bGameSessionCreated;

	FCSOnStartSessionComplete OnStartSessionCompleteEvent;

	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	virtual void RegisterServer() override;
	virtual void OnCreateSessionComplete(FName SsName, bool bWasSuccessful);
	//void StartSession();
};
