#pragma once

#include "Engine/GameTool/Movement/Input/IInputListener.h"
#include "Engine/GameTool/Movement/MoveComponent.h"

class EditorController : public MoveComponent, public IInputListener
{
public:
	EditorController(Actor* pActor);

	void Update() override;
	void OnNotify(SDL_Event& pEvent) override;

private:
	float mMovementSpeed = 5.0f;

	Vector2 inputDirection = Vector2::ZERO;
};

