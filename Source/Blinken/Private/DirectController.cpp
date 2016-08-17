// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "BlinkenPrivatePCH.h"
#include "DirectController.h"

FDirectController::FDirectController() : FBaseController()
{	
}

void FDirectController::SetGlobalColor(const FColor color)
{
	if (!bEnabled)
	{
		return;
	}

	// clear any flash effects
	targetColor = color;
	targetTimeLeft = 0;
	targetDuration = 0;

	FBaseController::SetGlobalColor(color);
}

void FDirectController::FlashColor(FColor color, float duration)
{
	if (!bEnabled)
	{
		return;
	}

	targetColor = color;
	targetTimeLeft = duration;
	targetDuration = duration;

	// Tick() takes care of actually setting the appropriate color
}

void FDirectController::Tick(float DeltaTime)
{
	if (!bEnabled)
	{
		return;
	}

	accumulatedTime += DeltaTime;

	if (accumulatedTime < 0.1f)
	{
		return;
	}

	if (targetTimeLeft > 0.0f)
	{
		float progressToGlobalColor = 1.0f - (targetTimeLeft / targetDuration);
		FColor currentColor;
		currentColor.R = FMath::Lerp(targetColor.R, globalColor.R, progressToGlobalColor);
		currentColor.G = FMath::Lerp(targetColor.G, globalColor.G, progressToGlobalColor);
		currentColor.B = FMath::Lerp(targetColor.B, globalColor.B, progressToGlobalColor);

		targetTimeLeft -= accumulatedTime;

		if (targetTimeLeft <= 0.0f)
		{
			currentColor = globalColor;
		}

		SetCurrentColor(currentColor);
	}

	accumulatedTime = 0.0f;
}
