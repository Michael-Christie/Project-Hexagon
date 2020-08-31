// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingEnemy.h"
#include "Components/CapsuleComponent.h"
#include "../Player/HexagonPlayerController.h"
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "../EnemyController.h"

#include "../Player/Projectile.h"

// Sets default values
// Sets default values
AShootingEnemy::AShootingEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AShootingEnemy::OnOverlapBegin);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f);

	PawnSense = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Sense Component"));
}

// Called when the game starts or when spawned
void AShootingEnemy::BeginPlay()
{
	Super::BeginPlay();

	PawnSense->OnSeePawn.AddDynamic(this, &AShootingEnemy::OnPawnSeen);
}

void AShootingEnemy::HitDamage(float amount)
{
	EnemyHealth -= amount;

	if (EnemyHealth <= 0)
		Destroy();
}

void AShootingEnemy::OnOverlapBegin(UPrimitiveComponent * overlappingComponent, AActor * otherActor, UPrimitiveComponent * otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult & sweepResult)
{
	AHexagonPlayerController* player = Cast<AHexagonPlayerController>(otherActor);

	if (player != nullptr)
	{
		//player can be destoryed
		player->Destroy();
	}
}

void AShootingEnemy::OnPawnSeen(APawn * seenPawn)
{
	if (seenPawn == nullptr)
		return;
	////Find the direction to the seen pawn
	//FVector direction = seenPawn->GetActorLocation() - GetActorLocation();
	//direction.Normalize();

	//FRotator lookAt = FRotationMatrix::MakeFromX(direction).Rotator();
	//lookAt.Pitch = 0;
	//lookAt.Roll = 0;

	//SetActorRotation(lookAt);

	//Find the AI controller
	AEnemyController* EController = Cast<AEnemyController>(GetController());

	if (EController == nullptr) return;

	//Move to the actor;
	EController->K2_SetFocalPoint(seenPawn->GetActorLocation());

	if (canShoot) 
	{
		UWorld* world = GetWorld();
		if (world == nullptr)return;

		FVector direction = seenPawn->GetActorLocation() - GetActorLocation();
		direction.Normalize();

		FRotator spawnRotation = FRotationMatrix::MakeFromX(direction).Rotator();
		FVector spawnLocation = GetActorLocation();

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		ActorSpawnParams.Instigator = this;

		AProjectile* p = world->SpawnActor<AProjectile>(ProjectileClass, spawnLocation, spawnRotation, ActorSpawnParams);

		if (p) {
			FVector LaunchDirection = spawnRotation.Vector();
			p->SetUp(LaunchDirection, nullptr);
		}
	}
}

// Called every frame
void AShootingEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShootingEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

