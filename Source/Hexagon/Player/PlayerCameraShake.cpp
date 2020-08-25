// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCameraShake.h"

UPlayerCameraShake::UPlayerCameraShake()
{
	OscillationDuration = 0.25f;
	OscillationBlendInTime = 0.05f;
	OscillationBlendOutTime = 0.05f;

	RotOscillation.Pitch.Amplitude = 3.0f;
	RotOscillation.Pitch.Frequency = 25.0f;

	RotOscillation.Yaw.Amplitude = 3.0f;
	RotOscillation.Yaw.Frequency = 25.0f;
}