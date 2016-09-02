#pragma once

#include "EngineMinimal.h"

class FLogitechGLEDController : public FBaseController
{
public:
	FLogitechGLEDController();

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual void Tick(float DeltaTime) override;

	virtual void FlashColor(FColor color, float duration) override;

protected:
	virtual void SetCurrentColor(const FColor color) override;

protected:
	static FLogitechGLEDController* Singleton;

public:
	static FLogitechGLEDController* Get();

protected:
	void toRGBpercent(const FColor color, int &red, int &green, int &blue) const;
	FColor toFColor(const int red, const int green, const int blue) const;
};
