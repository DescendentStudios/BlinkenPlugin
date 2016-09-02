// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "BlinkenPrivatePCH.h"
#include "Blinken.h"
#include "BlinkenBPLibrary.h"

UBlinkenBPLibrary::UBlinkenBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void UBlinkenBPLibrary::Enable(bool value)
{
	FBlinkenModule::Get().Enable(value);
}

bool UBlinkenBPLibrary::IsEnabled()
{
	return FBlinkenModule::Get().IsEnabled();
}

void UBlinkenBPLibrary::SetGlobalColor(FColor color)
{
	FBlinkenModule::Get().SetGlobalColor(color);
}

void UBlinkenBPLibrary::FlashColor(FColor color, float duration)
{
	FBlinkenModule::Get().FlashColor(color, duration);
}