// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetDistanceTo(Points[index]) > 10)
	{
		//Finds the direction
		FVector direction = Points[index]->GetActorLocation() - GetActorLocation();
		direction.Normalize();
		//finds the speed
		float amount = speed * DeltaTime;

		FVector NewLocation = GetActorLocation();

		NewLocation += direction * amount;

		SetActorLocation(NewLocation);

	}
	else
	{
		//your at the target, Move on to the next one
		index++;
		if (index > Points.Num() - 1)
			index = index % Points.Num();
	}
}

