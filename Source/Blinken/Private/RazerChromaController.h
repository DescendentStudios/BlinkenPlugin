#pragma once

#include "EngineMinimal.h"
#include "DirectController.h"

#if PLATFORM_WINDOWS
#include "AllowWindowsPlatformTypes.h"
#include "RzChromaSDKDefines.h"
#include "RzChromaSDKTypes.h"
#include "RzErrors.h"
#include "HideWindowsPlatformTypes.h"
#endif

class FRazerChromaController : public FDirectController
{
public:
	FRazerChromaController();

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

protected:
	virtual void SetCurrentColor(const FColor color) override;

protected:
	static FRazerChromaController* Singleton;

public:
	static FRazerChromaController* Get();

protected:

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

	HMODULE hLibrary = nullptr;

	INIT Init = nullptr;
	UNINIT UnInit = nullptr;
	CREATEEFFECT CreateEffect = nullptr;
	CREATEKEYBOARDEFFECT CreateKeyboardEffect = nullptr;
	CREATEMOUSEEFFECT CreateMouseEffect = nullptr;
	CREATEHEADSETEFFECT CreateHeadsetEffect = nullptr;
	CREATEMOUSEPADEFFECT CreateMousepadEffect = nullptr;
	CREATEKEYPADEFFECT CreateKeypadEffect = nullptr;
	SETEFFECT SetEffect = nullptr;
	DELETEEFFECT DeleteEffect = nullptr;
	QUERYDEVICE QueryDevice = nullptr;
#endif

protected:
	typedef uint32 RazerRGB;

	RazerRGB toRazerRGB(const FColor color) const;
};