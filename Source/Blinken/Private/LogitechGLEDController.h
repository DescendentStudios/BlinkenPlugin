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
	bool bEnabled;

protected:
	static FLogitechGLEDController* Singleton;

public:
	static FLogitechGLEDController* Get();

protected:
	void toRGBpercent(FColor color, int &red, int &green, int &blue);
	FColor toFColor(int red, int green, int blue);
};
