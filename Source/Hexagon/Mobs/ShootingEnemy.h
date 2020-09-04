// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interfaces/Damageable.h"
#include "ShootingEnemy.generated.h"

UCLASS()
class HEXAGON_API AShootingEnemy : public ACharacter, public IDamageable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShootingEnemy();
	float EnemyHealth = 50;
	bool canShoot = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void HitDamage(float amount) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent * overlappingComponent, AActor * otherActor, UPrimitiveComponent * otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult & sweepResult);


	UFUNCTION()
		void OnPawnSeen(APawn* seenPawn);

	FTimerHandle TimerHandle_ResetShooting;

	void ResetShooting();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = AI)
		class UPawnSensingComponent* PawnSense;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AProjectile> ProjectileClass;

};
