#pragma once

#include "Actor.h"

class MoveComponent;
class FPSController;

class Camera : public Actor
{
public:
	Camera();
	void SetupComponents() override {};
	void Update() override;

private:
	FPSController* mMoveComponent;
};

