// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "BlinkenPrivatePCH.h"
#include "LogitechGLEDController.h"

#if PLATFORM_WINDOWS
#include "AllowWindowsPlatformTypes.h"
#include "LogitechLEDLib.h"
#include "HideWindowsPlatformTypes.h"
#endif

/**
* Holds the singleton pointer
*/
FLogitechGLEDController* FLogitechGLEDController::Singleton = nullptr;

FLogitechGLEDController* FLogitechGLEDController::Get()
{
	if (Singleton == nullptr)
	{
		Singleton = new FLogitechGLEDController();
	}

	return Singleton;
}

FLogitechGLEDController::FLogitechGLEDController() : FBaseController()
{
}

void FLogitechGLEDController::StartupModule()
{	
#if PLATFORM_WINDOWS
	bEnabled = LogiLedInit();	
#endif
}

void FLogitechGLEDController::ShutdownModule()
{
	if (bEnabled)
	{
		bEnabled = false;
#if PLATFORM_WINDOWS
		LogiLedShutdown();
#endif
	}
}

void FLogitechGLEDController::SetCurrentColor(const FColor color)
{
	if (!bEnabled)
	{
		return;
	}

	int redPercentage = 0;
	int greenPercentage = 0;
	int bluePercentage = 0;
	toRGBpercent(color, redPercentage, greenPercentage, bluePercentage);
#if PLATFORM_WINDOWS
	LogiLedSetLighting(redPercentage, greenPercentage, bluePercentage);
#endif
}

void FLogitechGLEDController::FlashColor(FColor color, float duration)
{
	if (!bEnabled)
	{
		return;
	}

	int redPercentage = 0;
	int greenPercentage = 0;
	int bluePercentage = 0;
	toRGBpercent(color, redPercentage, greenPercentage, bluePercentage);

	int durationMS = duration * 1000;

#if PLATFORM_WINDOWS
	LogiLedFlashLighting(redPercentage, greenPercentage, bluePercentage, durationMS, durationMS);
#endif
}

void FLogitechGLEDController::Tick(float DeltaTime)
{
}

void FLogitechGLEDController::toRGBpercent(const FColor color, int &red, int &green, int &blue) const
{
	red = (int)((color.R / 255.0f) * 100);
	green = (int)((color.G / 255.0f) * 100);
	blue = (int)((color.B / 255.0f) * 100);
}

FColor FLogitechGLEDController::toFColor(const int red, const int green, const int blue) const
{
	const int newRed = (int)((red / 100.0f) * 255);
	const int newGreen = (int)((green / 100.0f) * 255);
	const int newBlue = (int)((blue / 100.0f) * 255);
	return FColor(newRed, newGreen, newBlue);
}