// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerFunction.h"
#include "Components/TextBlock.h"

void UTimerFunction::EndTime()
{
	timeRunning = false;
}

void UTimerFunction::Timer(float Delta)
{
	if (timeRunning)
	{
		time += Delta;
		int seconds = FMath::RoundToInt((time * 100));
		float fSeconds = seconds / 100.0f;

		//TimerLable->SetText(FText::FromString(FString::SanitizeFloat(fSeconds,2)));
	}
}

void UTimerFunction::StartTime()
{
	timeRunning = true;
}


