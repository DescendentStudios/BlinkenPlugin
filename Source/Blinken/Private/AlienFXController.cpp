// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "BlinkenPrivatePCH.h"
#include "AlienFXController.h"

/**
* Holds the singleton pointer
*/
FAlienFXController* FAlienFXController::Singleton = nullptr;

FAlienFXController* FAlienFXController::Get()
{
	if (Singleton == nullptr)
	{
		Singleton = new FAlienFXController();
	}

	return Singleton;
}

FAlienFXController::FAlienFXController()
{
}

void FAlienFXController::StartupModule()
{	
#if PLATFORM_WINDOWS
	// Startup
	hLibrary = LoadLibrary(_T(LFX_DLL_NAME));

	if (hLibrary)
	{
		// GetProcAddress will throw 4191 because it's an unsafe type cast, but I almost know what I'm doing here
#pragma warning(disable: 4191)
		initFunction = (LFX2INITIALIZE)GetProcAddress(hLibrary, LFX_DLL_INITIALIZE);
		releaseFunction = (LFX2RELEASE)GetProcAddress(hLibrary, LFX_DLL_RELEASE);
		versionFunction = (LFX2GETVERSION)GetProcAddress(hLibrary, LFX_DLL_GETVERSION);

		resetFunction = (LFX2RESET)GetProcAddress(hLibrary, LFX_DLL_RESET);
		updateFunction = (LFX2UPDATE)GetProcAddress(hLibrary, LFX_DLL_UPDATE);

		getNumDevicesFunction = (LFX2GETNUMDEVICES)GetProcAddress(hLibrary, LFX_DLL_GETNUMDEVICES);
		getDeviceDescriptionFunction = (LFX2GETDEVDESC)GetProcAddress(hLibrary, LFX_DLL_GETDEVDESC);

		getNumLightsFunction = (LFX2GETNUMLIGHTS)GetProcAddress(hLibrary, LFX_DLL_GETNUMLIGHTS);
		setLightColorFunction = (LFX2SETLIGHTCOL)GetProcAddress(hLibrary, LFX_DLL_SETLIGHTCOL);
		getLightColorFunction = (LFX2GETLIGHTCOL)GetProcAddress(hLibrary, LFX_DLL_GETLIGHTCOL);
		getLightDescriptionFunction = (LFX2GETLIGHTDESC)GetProcAddress(hLibrary, LFX_DLL_GETLIGHTDESC);

		lightFunction = (LFX2LIGHT)GetProcAddress(hLibrary, LFX_DLL_LIGHT);
		lightActionColorFunction = (LFX2ACTIONCOLOR)GetProcAddress(hLibrary, LFX_DLL_ACTIONCOLOR);
		lightActionColorExFunction = (LFX2ACTIONCOLOREX)GetProcAddress(hLibrary, LFX_DLL_ACTIONCOLOREX);
		setTiming = (LFX2SETTIMING)GetProcAddress(hLibrary, LFX_DLL_SETTIMING);
#pragma warning(default: 4191)
	}

	if (initFunction && releaseFunction && versionFunction &&
		resetFunction && updateFunction && 
		getNumDevicesFunction && getDeviceDescriptionFunction &&
		getNumLightsFunction && setLightColorFunction && getLightColorFunction && getLightDescriptionFunction &&
		lightFunction && lightActionColorFunction && lightActionColorExFunction && setTiming
		)
	{
		LFX_RESULT result = initFunction();
		if (result == LFX_SUCCESS)
		{
			result = resetFunction();
			bEnabled = true;
		}
	}
#endif
}

void FAlienFXController::ShutdownModule()
{
	if (bEnabled)
	{
		bEnabled = false;

#if PLATFORM_WINDOWS
		// Shutdown
		LFX_RESULT result = releaseFunction();
#endif
	}

#if PLATFORM_WINDOWS
	if (hLibrary)
	{
		FreeLibrary(hLibrary);
		hLibrary = nullptr;
	}
#endif
}

void FAlienFXController::SetGlobalColor(const FColor color)
{
	if (!bEnabled)
	{
		return;
	}

#if PLATFORM_WINDOWS
	LFXColorVal myColor = toLFXColorVal(color);
	LFX_RESULT result = resetFunction();	
	result = lightFunction(LFX_ALL, myColor);
	result = updateFunction();
#endif
}

#if PLATFORM_WINDOWS
LFX_COLOR FAlienFXController::toLFXColor(const FColor color) const
{
	LFX_COLOR myColor;

	myColor.red = color.R;
	myColor.green = color.G;
	myColor.blue = color.B;
	myColor.brightness = 255;

	return myColor;
}

FAlienFXController::LFXColorVal FAlienFXController::toLFXColorVal(const FColor color) const
{
	/* 
	From SDK:
		Color is packed into a 32-bit value, as follows:
		Bits 0-7: Blue
		Bits 8-15: Green
		Bits 16-23: Red
		Bits 24-32: Brightness
	*/
	LFXColorVal myColor;

	myColor = ((uint32)(((uint8)(color.B) | ((uint16)((uint8)(color.G)) << 8)) | (((uint32)(uint8)(color.R)) << 16)));

	myColor |= LFX_FULL_BRIGHTNESS;

	return myColor;
}
#endif
