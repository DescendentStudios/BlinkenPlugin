// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include <vector>

#include "ModuleManager.h"
#include "Tickable.h"

class FBaseController;

class FBlinkenModule : public IModuleInterface, FTickableGameObject
{
public:
	FBlinkenModule() { }
	~FBlinkenModule() { }

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** FTickableObjectBase implementation */
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return true; }
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(FBlinkenModule, STATGROUP_Tickables); }

protected:
	void CreateControllers();

protected:
	std::vector<FBaseController*> controllers;
};