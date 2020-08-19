// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"


void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyController::GoToTarget(AActor* actor)
{
	MoveToActor(actor);
}
