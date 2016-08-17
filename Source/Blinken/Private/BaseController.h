#pragma once

#include "EngineMinimal.h"

class FBaseController
{
public:
	FBaseController();

	virtual void StartupModule() = 0;
	virtual void ShutdownModule() = 0;

	virtual void Tick(float DeltaTime) = 0;

	virtual void SetGlobalColor(const FColor color);
	virtual void FlashColor(FColor color, float duration) = 0;

protected:
	virtual void SetCurrentColor(const FColor color) = 0;

protected:
	bool bEnabled = false;
	FColor globalColor;
};