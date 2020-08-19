// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/CapsuleComponent.h"
#include "../Player/HexagonPlayerController.h"
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "../EnemyController.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f);

	PawnSense = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Sense Component"));
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	PawnSense->OnSeePawn.AddDynamic(this, &AEnemy::OnPawnSeen);
}

void AEnemy::HitDamage(float amount)
{
	EnemyHealth -= amount;

	if (EnemyHealth <= 0)
		Destroy();
}

void AEnemy::OnOverlapBegin(UPrimitiveComponent * overlappingComponent, AActor * otherActor, UPrimitiveComponent * otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult & sweepResult)
{
	AHexagonPlayerController* player = Cast<AHexagonPlayerController>(otherActor);

	if (player != nullptr) 
	{
		//player can be destoryed
		player->Destroy();
	}
}

void AEnemy::OnPawnSeen(APawn * seenPawn)
{
	if (seenPawn == nullptr)
		return;

	//Find the AI controller
	AEnemyController* EController = Cast<AEnemyController>(GetController());

	if (EController == nullptr) return;

	//Move to the actor;
	EController->GoToTarget(seenPawn);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

