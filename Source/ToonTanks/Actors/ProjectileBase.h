// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class UCameraShake;

UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

	//Camera shake
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FX", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShake> HitShake;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 1300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	float Damage = 50.f;

	//This is declared in ProjectileBase parent class, and this event executes, when we hit something
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//Playing effects
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FX", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* HitParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* ParticleTrail;

	//Playing sound
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FX", meta = (AllowPrivateAccess = "true"))
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FX", meta = (AllowPrivateAccess = "true"))
	USoundBase* HitSound;


 

};
