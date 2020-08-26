// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelEnd.generated.h"

UCLASS()
class HEXAGON_API ALevelEnd : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelEnd();

	UPROPERTY(VisibleDefaultsOnly, Category = Component)
		class USphereComponent* HitCollider;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void LevelOver(AActor * otherActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Next Level")
		FString NextLevelName;

};
