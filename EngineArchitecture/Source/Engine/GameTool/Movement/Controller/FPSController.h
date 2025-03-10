#pragma once

#include "Engine/GameTool/Movement/Input/IInputListener.h"
#include "Engine/GameTool/Movement/MoveComponent.h"

class FPSController : public MoveComponent, public IInputListener
{
public:
	FPSController(Actor* pActor);

	void Update() override;
	void OnNotify(SDL_Event& pEvent) override;

private:
	float mMovementSpeed = 5.0f;
};

