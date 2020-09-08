// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerFunction.generated.h"

/**
 * 
 */
UCLASS()
class HEXAGON_API UTimerFunction : public UUserWidget
{
	GENERATED_BODY()
private:
	bool timeRunning = false;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float time = 0;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TimerLable;

	UFUNCTION(BlueprintCallable)
		void Timer(float Delta);

	UFUNCTION(BlueprintCallable)
		void StartTime();
	UFUNCTION(BlueprintCallable)
		void EndTime();
};
