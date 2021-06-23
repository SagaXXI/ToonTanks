// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class ATanksGameMode;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

private:

	//This is created to be able to change max health value in blueprints, defaults, etc.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"));
	float DefaultHealth = 100.f;

	float Health = 0.f;

	AActor* Owner;

	//Game mode reference, to play some dead functions in it, it is good to be more cleaner in code, because if we won't use gamemode,
	//then everyone should create pointers to each other, and call functions, for example dead function.
	//So it is good to use game mode instead.
	ATanksGameMode* GameModeRef;


		
};
