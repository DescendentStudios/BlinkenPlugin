// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "BlinkenPrivatePCH.h"
#include "RazerChromaController.h"
#include "LogitechGLEDController.h"
#include "AlienFXController.h"

#define LOCTEXT_NAMESPACE "FBlinkenModule"

void FBlinkenModule::CreateControllers()
{
	controllers.push_back(FRazerChromaController::Get());
	controllers.push_back(FLogitechGLEDController::Get());
	controllers.push_back(FAlienFXController::Get());
}

void FBlinkenModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FRazerChromaController::Get()->StartupModule();
	FLogitechGLEDController::Get()->StartupModule();
	FAlienFXController::Get()->StartupModule();

	/*
	CreateControllers();

	for (const auto i : controllers)
	{
		i->StartupModule();
	}
	*/
}

void FBlinkenModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	FRazerChromaController::Get()->ShutdownModule();
	FLogitechGLEDController::Get()->ShutdownModule();
	FAlienFXController::Get()->ShutdownModule();

	/*
	for (const auto i : controllers)
	{
		i->ShutdownModule();
	}
	*/
}

void FBlinkenModule::Tick(float DeltaTime)
{
	FRazerChromaController::Get()->Tick(DeltaTime);
	FLogitechGLEDController::Get()->Tick(DeltaTime);
	FAlienFXController::Get()->Tick(DeltaTime);

	/*
	for (const auto i : controllers)
	{
		i->Tick(DeltaTime);
	}
	*/
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBlinkenModule, Blinken)