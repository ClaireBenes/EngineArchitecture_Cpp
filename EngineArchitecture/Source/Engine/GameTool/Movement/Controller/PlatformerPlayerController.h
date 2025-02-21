#pragma once

#include "Engine/GameTool/Movement/Input/IInputListener.h"
#include "Engine/GameTool/Movement/MoveComponent.h"

class PlatformerPlayerController : public MoveComponent, public IInputListener
{
public:
	PlatformerPlayerController(Actor* pActor);

	void OnNotify(SDL_Event& pEvent) override;

private:
	Vector2 mForce = { 0, -4 };
	bool mIsJumping = false;
};

