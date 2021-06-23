// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

class APawnTank;

UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

	APawnTurret();

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

private:

	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))	
	float FireRate = 2.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange = 500.f;

	//Check for player to fire
	void CheckFireCondition();

	float ReturnDistanceToPlayer();

	//For checking distance between turret and tank
	APawnTank* PlayerPawn;
	//Loop firing (Automatic (almost) fire)
	FTimerHandle FireRateTimerHandle;

	

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void HandleDestruction() override;

	
};
