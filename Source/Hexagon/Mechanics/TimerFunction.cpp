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
		TimerLable->SetText(FText::FromString(FString::SanitizeFloat(time)));
	}
}

void UTimerFunction::StartTime()
{
	timeRunning = true;
}


