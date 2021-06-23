// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TanksGameMode.generated.h"

/**
 * 
 */
class APawnTank;
class ATanksPlayerController;

UCLASS()
class TOONTANKS_API ATanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	void ActorDied(AActor* DeadActor);

	UFUNCTION(BlueprintImplementableEvent)	
	void GameStart();
	
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);

protected:
	virtual void BeginPlay() override;

private:
	void HandleGameStart();

	void HandleGameOver(bool PlayerWon);

	int32 TargetTurrets = 0;
	int32 GetCurrentTurretsCount();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Loop", meta = (AllowPrivateAccess = "true"))
	int StartDelay = 3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	APawnTank* PlayerPawn;

	ATanksPlayerController* PlayerControllerRef;
};
