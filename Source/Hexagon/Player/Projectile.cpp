// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Engine/Engine.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../Interfaces/Damageable.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "HexagonPlayerController.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Hit Area"));
	HitCollider->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	RootComponent = HitCollider;

	HitCollider->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovement->SetUpdatedComponent(HitCollider);
	ProjectileMovement->InitialSpeed = 4000.0f;
	ProjectileMovement->MaxSpeed = 4000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 0.3f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->SetupAttachment(HitCollider);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ProjectileMesh->AddLocalRotation(FRotator(7.5f, 0, 0));

}

void AProjectile::SetUp(FVector direction, AHexagonPlayerController * player)
{
	//adds a velocity to the direction its facing
	ProjectileMovement->Velocity = direction * ProjectileMovement->InitialSpeed;
	playerContoller = player;
}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	//if the object is just simulating physics
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovement->Velocity * 100.0f, Hit.ImpactPoint);
	}
	else //if the object has the damagable interface;
	{
		IDamageable* damageInteface = Cast<IDamageable>(OtherActor);

		if (damageInteface != nullptr)
		{
			damageInteface->HitDamage(50.0f);
			
			if(playerContoller != nullptr)
				playerContoller->EnemyHitCall();

			if(HitParticle != nullptr)
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetTransform(), true);
		}
	}

	if (OtherActor != this)
		Destroy();
}

