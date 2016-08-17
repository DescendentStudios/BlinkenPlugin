// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "BlinkenPrivatePCH.h"
#include "BlinkenBPLibrary.h"
#include "RazerChromaController.h"

UBlinkenBPLibrary::UBlinkenBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void UBlinkenBPLibrary::SetGlobalColor(FColor color)
{
	// TODO: Use FBlinkenModule::controllers instead of explicitly calling each one
	FRazerChromaController::Get()->SetGlobalColor(color);
	FLogitechGLEDController::Get()->SetGlobalColor(color);
	FAlienFXController::Get()->SetGlobalColor(color);
}

void UBlinkenBPLibrary::FlashColor(FColor color, float duration)
{
	// TODO: Use FBlinkenModule::controllers instead of explicitly calling each one
	FRazerChromaController::Get()->FlashColor(color, duration);
	FLogitechGLEDController::Get()->FlashColor(color, duration);
	FAlienFXController::Get()->FlashColor(color, duration);
}