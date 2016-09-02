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
	
	// Load DLL
	const TCHAR* pluginLibPath = TEXT("Blinken/ThirdParty/AlienFXSDK/dll/");
	FString libraryPath;

	const FString EnginePluginsDir = FPaths::ConvertRelativePathToFull(FPaths::EnginePluginsDir());
	const FString FullEnginePluginsDir = EnginePluginsDir + pluginLibPath + FPlatformProcess::GetBinariesSubdirectory() + TEXT("/");
	if (FPaths::DirectoryExists(FullEnginePluginsDir))
	{
		libraryPath = FullEnginePluginsDir;
	}
	else
	{
		const FString PluginsDir = FPaths::ConvertRelativePathToFull(FPaths::GamePluginsDir());
		libraryPath = PluginsDir + pluginLibPath + FPlatformProcess::GetBinariesSubdirectory() + TEXT("/");
	}
	FPlatformProcess::PushDllDirectory(*libraryPath);
	hLibrary = FPlatformProcess::GetDllHandle(TEXT(LFX_DLL_NAME));
	FPlatformProcess::PopDllDirectory(*libraryPath);

	// Get function pointers
	if (hLibrary)
	{
		initFunction = (LFX2INITIALIZE)FPlatformProcess::GetDllExport(hLibrary, TEXT(LFX_DLL_INITIALIZE));
		releaseFunction = (LFX2RELEASE)FPlatformProcess::GetDllExport(hLibrary, TEXT(LFX_DLL_RELEASE));
		versionFunction = (LFX2GETVERSION)FPlatformProcess::GetDllExport(hLibrary, TEXT(LFX_DLL_GETVERSION));

		resetFunction = (LFX2RESET)FPlatformProcess::GetDllExport(hLibrary, TEXT(LFX_DLL_RESET));
		updateFunction = (LFX2UPDATE)FPlatformProcess::GetDllExport(hLibrary, TEXT(LFX_DLL_UPDATE));

		getNumDevicesFunction = (LFX2GETNUMDEVICES)FPlatformProcess::GetDllExport(hLibrary, TEXT(LFX_DLL_GETNUMDEVICES));
		getDeviceDescriptionFunction = (LFX2GETDEVDESC)FPlatformProcess::GetDllExport(hLibrary, TEXT(LFX_DLL_GETDEVDESC));

		getNumLightsFunction = (LFX2GETNUMLIGHTS)FPlatformProcess::GetDllExport(hLibrary, TEXT(LFX_DLL_GETNUMLIGHTS));
		setLightColorFunction = (LFX2SETLIGHTCOL)FPlatformProcess::GetDllExport(hLibrary, TEXT(LFX_DLL_SETLIGHTCOL));
		getLightColorFunction = (LFX2GETLIGHTCOL)FPlatformProcess::GetDllExport(hLibrary, TEXT(LFX_DLL_GETLIGHTCOL));
		getLightDescriptionFunction = (LFX2GETLIGHTDESC)FPlatformProcess::GetDllExport(hLibrary, TEXT(LFX_DLL_GETLIGHTDESC));

		lightFunction = (LFX2LIGHT)FPlatformProcess::GetDllExport(hLibrary, TEXT(LFX_DLL_LIGHT));
		lightActionColorFunction = (LFX2ACTIONCOLOR)FPlatformProcess::GetDllExport(hLibrary, TEXT(LFX_DLL_ACTIONCOLOR));
		lightActionColorExFunction = (LFX2ACTIONCOLOREX)FPlatformProcess::GetDllExport(hLibrary, TEXT(LFX_DLL_ACTIONCOLOREX));
		setTiming = (LFX2SETTIMING)FPlatformProcess::GetDllExport(hLibrary, TEXT(LFX_DLL_SETTIMING));
	}

	// init library
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
		FPlatformProcess::FreeDllHandle(hLibrary);
		hLibrary = nullptr;
	}
#endif
}

void FAlienFXController::SetCurrentColor(const FColor color)
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
