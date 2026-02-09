#pragma once

#include "Engine/GameTool/Movement/Input/IInputListener.h"
#include "Engine/GameTool/Movement/MoveComponent.h"

class TheDescentPlayer;

class PilotController : public MoveComponent, public IInputListener
{
public:
	PilotController(Actor* pActor);
	~PilotController();

	void Update() override;
	void OnNotify(SDL_Event& pEvent) override;

	Vector3 GetDesiredPos() override;
	void OnMousePress(SDL_MouseButtonEvent& b);

private:
	float mMovementSpeed = 5.0f;
	Vector3 inputDirection = Vector3::Zero;

	TheDescentPlayer* mPlayer = nullptr;
};

