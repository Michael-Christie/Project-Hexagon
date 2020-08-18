// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Engine/Engine.h"
#include "Components/SphereComponent.h"
#include "../Interfaces/Damageable.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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

	// Die after 1 seconds.
	InitialLifeSpan = 1.0f;



}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(InitialLifeSpan);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::SetUp(FVector direction)
{
	//adds a velocity to the direction its facing
	ProjectileMovement->Velocity = direction * ProjectileMovement->InitialSpeed;
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
		}
	}

	if(OtherActor != this)
		Destroy();
}

