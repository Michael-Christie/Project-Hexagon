// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelEnd.h"
#include "Components/SphereComponent.h"
#include "../Player/HexagonPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelEnd::ALevelEnd()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HitCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Hit Collider"));
	HitCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	HitCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	HitCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	//HitCollider->OnComponentBeginOverlap.AddDynamic(this, &ALevelEnd::LevelOver);
}

// Called when the game starts or when spawned
void ALevelEnd::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelEnd::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelEnd::LevelOver(AActor * otherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Colliding"));

	AHexagonPlayerController* player = Cast<AHexagonPlayerController>(otherActor);

	if (player != nullptr) 
	{
		//Level is over

		//stop player movement
		player->DisableInput(Cast<APlayerController>(player));

		//Add the UI

	}
}

