// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TanksGameState.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATanksGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	ATanksGameState();
	
	UFUNCTION(BlueprintCallable)
	float GetScore();

	void IncrementScore();
private:

	float Score;

	
	
};
