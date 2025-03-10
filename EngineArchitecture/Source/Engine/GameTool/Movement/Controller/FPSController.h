#pragma once

#include "Engine/GameTool/Movement/Input/IInputListener.h"
#include "Engine/GameTool/Movement/MoveComponent.h"

class FPSController : public MoveComponent, public IInputListener
{
public:
	FPSController(Actor* pActor);

	void OnNotify(SDL_Event& pEvent) override;
};

