// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ToonTanks/TanksGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = DefaultHealth;

	GameModeRef = Cast<ATanksGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	Owner = GetOwner();
	if(Owner)
	{
		//Calling function on the OnTakeAnyDamage event
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Health component has no reference for an owner"));
	}
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage,
 const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage == 0 /* || Health == 0 */)
	{
		return;
	}
	//Making limit of Health variable, so it can't be less than zero
	Health = FMath::Clamp(Health - Damage, 0.f, DefaultHealth);
	if(Health == 0)
	{
		if(GameModeRef)
		{
			GameModeRef->ActorDied(Owner);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Health component has no reference for an owner"));
		}
	}
}