#pragma once

#include "EngineMinimal.h"

class FLogitechGLEDController
{
public:
	FLogitechGLEDController();

	void StartupModule();
	void ShutdownModule();

	void SetGlobalColor(const FColor color);

protected:
	bool bEnabled = false;

protected:
	static FLogitechGLEDController* Singleton;

public:
	static FLogitechGLEDController* Get();

protected:
	void toRGBpercent(const FColor color, int &red, int &green, int &blue) const;
	FColor toFColor(const int red, const int green, const int blue) const;
};
