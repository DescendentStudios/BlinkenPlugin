// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "BlinkenPrivatePCH.h"

#if PLATFORM_WINDOWS
#include "RazerChromaController.h"

using namespace ChromaSDK;
using namespace ChromaSDK::Keyboard;
using namespace ChromaSDK::Keypad;
using namespace ChromaSDK::Mouse;
using namespace ChromaSDK::Mousepad;
using namespace ChromaSDK::Headset;

#ifdef _WIN64
#define CHROMASDKDLL        _T("RzChromaSDK64.dll")
#else
#define CHROMASDKDLL        _T("RzChromaSDK.dll")
#endif
#endif

/**
* Holds the singleton pointer
*/
FRazerChromaController* FRazerChromaController::Singleton = nullptr;

FRazerChromaController* FRazerChromaController::Get()
{
	if (Singleton == nullptr)
	{
		Singleton = new FRazerChromaController();
	}

	return Singleton;
}

FRazerChromaController::FRazerChromaController()
{
	bChromaSDKEnabled = false;

#if PLATFORM_WINDOWS
	Init = nullptr;
	CreateEffect = nullptr;
	CreateKeyboardEffect = nullptr;
	CreateMouseEffect = nullptr;
	CreateHeadsetEffect = nullptr;
	CreateMousepadEffect = nullptr;
	CreateKeypadEffect = nullptr;
	SetEffect = nullptr;
	DeleteEffect = nullptr;
	QueryDevice = nullptr;
	UnInit = nullptr;
#endif
}

void FRazerChromaController::StartupModule()
{
#if PLATFORM_WINDOWS
	HMODULE ChromaSDKModule = nullptr;

	ChromaSDKModule = LoadLibrary(CHROMASDKDLL);
	if (ChromaSDKModule == NULL)
	{
		return;
	}

	// GetProcAddress will throw 4191 because it's an unsafe type cast, but I almost know what I'm doing here
#pragma warning(disable: 4191)
	RZRESULT Result = RZRESULT_INVALID;
	Init = (INIT)GetProcAddress(ChromaSDKModule, "Init");
	CreateEffect = (CREATEEFFECT)GetProcAddress(ChromaSDKModule, "CreateEffect");
	CreateKeyboardEffect = (CREATEKEYBOARDEFFECT)GetProcAddress(ChromaSDKModule, "CreateKeyboardEffect");
	CreateMouseEffect = (CREATEMOUSEEFFECT)GetProcAddress(ChromaSDKModule, "CreateMouseEffect");
	CreateHeadsetEffect = (CREATEHEADSETEFFECT)GetProcAddress(ChromaSDKModule, "CreateHeadsetEffect");
	CreateMousepadEffect = (CREATEMOUSEPADEFFECT)GetProcAddress(ChromaSDKModule, "CreateMousepadEffect");
	CreateKeypadEffect = (CREATEKEYPADEFFECT)GetProcAddress(ChromaSDKModule, "CreateKeypadEffect");
	SetEffect = (SETEFFECT)GetProcAddress(ChromaSDKModule, "SetEffect");
	DeleteEffect = (DELETEEFFECT)GetProcAddress(ChromaSDKModule, "DeleteEffect");
	QueryDevice = (QUERYDEVICE)GetProcAddress(ChromaSDKModule, "QueryDevice");
	UnInit = (UNINIT)GetProcAddress(ChromaSDKModule, "UnInit");
	if (Init)
	{
		Result = Init();
		if (Result == RZRESULT_SUCCESS)
		{
			if (CreateEffect &&
				CreateKeyboardEffect &&
				CreateMouseEffect &&
				CreateHeadsetEffect &&
				CreateMousepadEffect &&
				CreateKeypadEffect &&
				SetEffect &&
				DeleteEffect &&
				QueryDevice &&
				UnInit)
			{
				bChromaSDKEnabled = true;
			}
		}
	}
#pragma warning(default: 4191)
#endif
}

void FRazerChromaController::ShutdownModule()
{
	if (bChromaSDKEnabled)
	{
		bChromaSDKEnabled = false;
#if PLATFORM_WINDOWS
		UnInit();
#endif
	}
}

void FRazerChromaController::SetGlobalColor(const FColor color)
{
	if (!bChromaSDKEnabled)
	{
		return;
	}

	const uint32 myColor = RAZERRGB(color.R, color.G, color.B);

#if PLATFORM_WINDOWS

	// Might need to check that this isn't already set
	RZRESULT Result = RZRESULT_INVALID;

	ChromaSDK::Headset::STATIC_EFFECT_TYPE HeadsetEffect = {};
	HeadsetEffect.Color = myColor;
	Result = CreateHeadsetEffect(ChromaSDK::Headset::CHROMA_STATIC, &HeadsetEffect, NULL);

	ChromaSDK::Keyboard::STATIC_EFFECT_TYPE KeyboardEffect = {};
	KeyboardEffect.Color = myColor;
	Result = CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_STATIC, &KeyboardEffect, NULL);

	ChromaSDK::Keypad::STATIC_EFFECT_TYPE KeypadEffect = {};
	KeypadEffect.Color = myColor;
	Result = CreateKeypadEffect(ChromaSDK::Keypad::CHROMA_STATIC, &KeypadEffect, NULL);

	ChromaSDK::Mouse::STATIC_EFFECT_TYPE MouseEffect = {};
	MouseEffect.Color = myColor;
	Result = CreateMouseEffect(ChromaSDK::Mouse::CHROMA_STATIC, &MouseEffect, NULL);

	ChromaSDK::Mousepad::STATIC_EFFECT_TYPE MousepadEffect = {};
	MousepadEffect.Color = myColor;
	Result = CreateMousepadEffect(ChromaSDK::Mousepad::CHROMA_STATIC, &MousepadEffect, NULL);
#endif
}
