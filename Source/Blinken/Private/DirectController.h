#pragma once

#include "EngineMinimal.h"
#include "BaseController.h"

class FDirectController : public FBaseController
{
public:
	FDirectController();

	virtual void Tick(float DeltaTime) override;

	virtual void SetGlobalColor(const FColor color) override;
	virtual void FlashColor(FColor color, float duration) override;

protected:
	float accumulatedTime = 0.0f;
	FColor targetColor;
	float targetTimeLeft = 0.0f;
	float targetDuration = 0.0f;

protected:
	void ProcessFlash(const float deltaTime = 0.0f);
};