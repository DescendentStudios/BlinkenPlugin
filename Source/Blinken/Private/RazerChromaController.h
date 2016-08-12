#pragma once

#include "EngineMinimal.h"

#if PLATFORM_WINDOWS
#include "AllowWindowsPlatformTypes.h"
#include "RzChromaSDKDefines.h"
#include "RzChromaSDKTypes.h"
#include "RzErrors.h"
#include "HideWindowsPlatformTypes.h"
#endif

class FRazerChromaController
{
public:

#define RAZERRGB(r,g,b)          ((uint32)(((uint8)(r)|((uint16)((uint8)(g))<<8))|(((uint32)(uint8)(b))<<16)))

	const uint32 BLACK = RAZERRGB(0, 0, 0);
	const uint32 WHITE = RAZERRGB(255, 255, 255);
	const uint32 RED = RAZERRGB(255, 0, 0);
	const uint32 GREEN = RAZERRGB(0, 255, 0);
	const uint32 BLUE = RAZERRGB(0, 0, 255);
	const uint32 YELLOW = RAZERRGB(255, 255, 0);
	const uint32 PURPLE = RAZERRGB(128, 0, 128);
	const uint32 CYAN = RAZERRGB(0, 255, 255);
	const uint32 ORANGE = RAZERRGB(255, 165, 00);
	const uint32 PINK = RAZERRGB(255, 192, 203);
	const uint32 GREY = RAZERRGB(125, 125, 125);

	FRazerChromaController();

	void StartupModule();
	void ShutdownModule();

	void SetGlobalColor(const FColor color);

protected:
	bool bChromaSDKEnabled;

#if PLATFORM_WINDOWS
	typedef RZRESULT(*INIT)(void);
	typedef RZRESULT(*UNINIT)(void);
	typedef RZRESULT(*CREATEEFFECT)(RZDEVICEID DeviceId, ChromaSDK::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
	typedef RZRESULT(*CREATEKEYBOARDEFFECT)(ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
	typedef RZRESULT(*CREATEHEADSETEFFECT)(ChromaSDK::Headset::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
	typedef RZRESULT(*CREATEMOUSEPADEFFECT)(ChromaSDK::Mousepad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
	typedef RZRESULT(*CREATEMOUSEEFFECT)(ChromaSDK::Mouse::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
	typedef RZRESULT(*CREATEKEYPADEFFECT)(ChromaSDK::Keypad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
	typedef RZRESULT(*SETEFFECT)(RZEFFECTID EffectId);
	typedef RZRESULT(*DELETEEFFECT)(RZEFFECTID EffectId);
	typedef RZRESULT(*REGISTEREVENTNOTIFICATION)(HWND hWnd);
	typedef RZRESULT(*UNREGISTEREVENTNOTIFICATION)(void);
	typedef RZRESULT(*QUERYDEVICE)(RZDEVICEID DeviceId, ChromaSDK::DEVICE_INFO_TYPE &DeviceInfo);

	INIT Init;
	UNINIT UnInit;
	CREATEEFFECT CreateEffect;
	CREATEKEYBOARDEFFECT CreateKeyboardEffect;
	CREATEMOUSEEFFECT CreateMouseEffect;
	CREATEHEADSETEFFECT CreateHeadsetEffect;
	CREATEMOUSEPADEFFECT CreateMousepadEffect;
	CREATEKEYPADEFFECT CreateKeypadEffect;
	SETEFFECT SetEffect;
	DELETEEFFECT DeleteEffect;
	QUERYDEVICE QueryDevice;
#endif

protected:
	static FRazerChromaController* Singleton;

public:
	static FRazerChromaController* Get();
};