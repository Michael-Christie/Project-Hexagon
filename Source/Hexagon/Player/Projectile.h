// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class HEXAGON_API AProjectile : public AActor
{
	GENERATED_BODY()
	
		UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class USphereComponent* HitCollider;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class UStaticMeshComponent* ProjectileMesh;

	float InitialLifeSpan;
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetUp(FVector direction, class AHexagonPlayerController * player);
	class AHexagonPlayerController* playerContoller;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* HitParticle;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};
