// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "BlinkenPrivatePCH.h"
#include "RazerChromaController.h"

#if PLATFORM_WINDOWS

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
}

void FRazerChromaController::StartupModule()
{
#if PLATFORM_WINDOWS
	hLibrary = LoadLibrary(CHROMASDKDLL);
	if (hLibrary == NULL)
	{
		return;
	}

	// GetProcAddress will throw 4191 because it's an unsafe type cast
#pragma warning(disable: 4191)
	RZRESULT Result = RZRESULT_INVALID;
	Init = (INIT)GetProcAddress(hLibrary, "Init");
	QueryDevice = (QUERYDEVICE)GetProcAddress(hLibrary, "QueryDevice");
	UnInit = (UNINIT)GetProcAddress(hLibrary, "UnInit");

	CreateKeyboardEffect = (CREATEKEYBOARDEFFECT)GetProcAddress(hLibrary, "CreateKeyboardEffect");
	CreateMouseEffect = (CREATEMOUSEEFFECT)GetProcAddress(hLibrary, "CreateMouseEffect");
	CreateHeadsetEffect = (CREATEHEADSETEFFECT)GetProcAddress(hLibrary, "CreateHeadsetEffect");
	CreateMousepadEffect = (CREATEMOUSEPADEFFECT)GetProcAddress(hLibrary, "CreateMousepadEffect");
	CreateKeypadEffect = (CREATEKEYPADEFFECT)GetProcAddress(hLibrary, "CreateKeypadEffect");

	CreateEffect = (CREATEEFFECT)GetProcAddress(hLibrary, "CreateEffect");
	SetEffect = (SETEFFECT)GetProcAddress(hLibrary, "SetEffect");
	DeleteEffect = (DELETEEFFECT)GetProcAddress(hLibrary, "DeleteEffect");
#pragma warning(default: 4191)

	if (Init && UnInit && QueryDevice &&
		CreateKeyboardEffect && CreateMouseEffect && CreateHeadsetEffect && CreateMousepadEffect && CreateKeypadEffect &&
		CreateEffect && SetEffect && DeleteEffect && QueryDevice)
	{
		Result = Init();
		if (Result == RZRESULT_SUCCESS)
		{
			bEnabled = true;
		}
	}
#endif
}

void FRazerChromaController::ShutdownModule()
{
	if (bEnabled)
	{
		bEnabled = false;
#if PLATFORM_WINDOWS
		UnInit();
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

void FRazerChromaController::SetCurrentColor(const FColor color)
{
	const uint32 myColor = toRazerRGB(color);

#if PLATFORM_WINDOWS

	// simple API method from SDK docs frequently do not work (commented out below), use methods from SDK sample code instead
	// see file:///C:/Temp/razer-chroma-sdk/docs/_chroma_s_d_k_impl_8cpp-example.html

	// Might need to check that this isn't already set
	RZRESULT Result = RZRESULT_INVALID;

	// headset

	ChromaSDK::Headset::STATIC_EFFECT_TYPE HeadsetEffect = {};
	HeadsetEffect.Color = myColor;
	Result = CreateHeadsetEffect(ChromaSDK::Headset::CHROMA_STATIC, &HeadsetEffect, NULL);

	// keyboard

	/*
	ChromaSDK::Keyboard::STATIC_EFFECT_TYPE KeyboardEffect = {};
	KeyboardEffect.Color = myColor;
	Result = CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_STATIC, &KeyboardEffect, NULL);
	*/

	ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE KeyboardEffect = {};
	for (size_t row = 0; row<ChromaSDK::Keyboard::MAX_ROW; row++)
	{
		for (size_t col = 0; col<ChromaSDK::Keyboard::MAX_COLUMN; col++)
		{
			KeyboardEffect.Color[row][col] = myColor;
		}
	}

	CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &KeyboardEffect, NULL);

	// keypad

	/*
	ChromaSDK::Keypad::STATIC_EFFECT_TYPE KeypadEffect = {};
	KeypadEffect.Color = myColor;
	Result = CreateKeypadEffect(ChromaSDK::Keypad::CHROMA_STATIC, &KeypadEffect, NULL);
	*/

	ChromaSDK::Keypad::CUSTOM_EFFECT_TYPE KeypadEffect = {};

	for (size_t i = 0; i<ChromaSDK::Keypad::MAX_ROW; i++)
	{
		for (size_t j = 0; j<ChromaSDK::Keypad::MAX_COLUMN; j++)
		{
			KeypadEffect.Color[i][j] = myColor;
		}
	}

	CreateKeypadEffect(ChromaSDK::Keypad::CHROMA_CUSTOM, &KeypadEffect, NULL);

	// mouse
	
	/*
	ChromaSDK::Mouse::STATIC_EFFECT_TYPE MouseEffect = {};
	MouseEffect.Color = myColor;
	MouseEffect.LEDId = RZLED_ALL;
	Result = CreateMouseEffect(ChromaSDK::Mouse::CHROMA_STATIC, &MouseEffect, NULL);
	*/

	ChromaSDK::Mouse::CUSTOM_EFFECT_TYPE2 MouseEffect = {};
	for (int i = 0; i<Mouse::MAX_ROW; i++)
	{
		for (int j = 0; j<Mouse::MAX_COLUMN; j++)
		{
			MouseEffect.Color[i][j] = myColor;
		}
	}

	CreateMouseEffect(ChromaSDK::Mouse::CHROMA_CUSTOM2, &MouseEffect, NULL);

	// mousepad

	ChromaSDK::Mousepad::STATIC_EFFECT_TYPE MousepadEffect = {};
	MousepadEffect.Color = myColor;
	Result = CreateMousepadEffect(ChromaSDK::Mousepad::CHROMA_STATIC, &MousepadEffect, NULL);

#endif
}

FRazerChromaController::RazerRGB FRazerChromaController::toRazerRGB(const FColor color) const
{
	return ((uint32)(((uint8)(color.R) | ((uint16)((uint8)(color.G)) << 8)) | (((uint32)(uint8)(color.B)) << 16)));
}
