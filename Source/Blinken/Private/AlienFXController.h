#pragma once

#include "EngineMinimal.h"

#if PLATFORM_WINDOWS
#include "AllowWindowsPlatformTypes.h"
#include "LFX2.h"
#include "HideWindowsPlatformTypes.h"
#endif

class FAlienFXController
{
public:
	FAlienFXController();

	void StartupModule();
	void ShutdownModule();

	void SetGlobalColor(const FColor color);

protected:
	bool bEnabled = false;

protected:
	static FAlienFXController* Singleton;

public:
	static FAlienFXController* Get();

protected:
#if PLATFORM_WINDOWS
	typedef unsigned int LFXColorVal;

	//HINSTANCE hLibrary = nullptr;
	void* hLibrary = nullptr;

	LFX2INITIALIZE initFunction = nullptr;
	LFX2RELEASE releaseFunction = nullptr;
	LFX2GETVERSION versionFunction;

	LFX2RESET resetFunction = nullptr;
	LFX2UPDATE updateFunction = nullptr;

	LFX2GETNUMDEVICES getNumDevicesFunction = nullptr;
	LFX2GETDEVDESC getDeviceDescriptionFunction = nullptr;

	LFX2GETNUMLIGHTS getNumLightsFunction = nullptr;
	LFX2SETLIGHTCOL setLightColorFunction = nullptr;
	LFX2GETLIGHTCOL getLightColorFunction = nullptr;
	LFX2GETLIGHTDESC getLightDescriptionFunction = nullptr;

	LFX2LIGHT lightFunction;
	LFX2ACTIONCOLOR lightActionColorFunction;
	LFX2ACTIONCOLOREX lightActionColorExFunction;
	LFX2SETTIMING setTiming;

	LFX_COLOR toLFXColor(const FColor color) const;
	LFXColorVal toLFXColorVal(const FColor color) const;
#endif
};
