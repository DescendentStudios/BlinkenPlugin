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

	/**
	* Singleton-like access to this module's interface.  This is just for convenience!
	* Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	*
	* @return Returns singleton instance, loading the module on demand if needed
	*/
	static inline FBlinkenModule& Get()
	{
		return FModuleManager::LoadModuleChecked< FBlinkenModule >("Blinken");
	}

	/**
	* Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	*
	* @return True if the module is loaded and ready to use
	*/
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("Blinken");
	}
	
	// Functionality
	void Enable(bool value = true) { bEnabled = value; }
	bool IsEnabled() const { return bEnabled; }
	void SetGlobalColor(FColor color);
	void FlashColor(FColor color, float duration);

protected:
	void CreateControllers();

protected:
	std::vector<FBaseController*> controllers;
	bool bEnabled = true;
};