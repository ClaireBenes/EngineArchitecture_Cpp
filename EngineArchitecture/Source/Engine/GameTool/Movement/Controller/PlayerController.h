#pragma once

#include "Engine/GameTool/Movement/Input/IInputListener.h"
#include "Engine/GameTool/Movement/MoveComponent.h"

class PlayerController : public MoveComponent, public IInputListener
{
public:
	PlayerController(Actor* pActor);

	void OnNotify(SDL_Event& pEvent) override;
};

