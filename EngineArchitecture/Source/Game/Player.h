#pragma once

#include "Engine/GameTool/Actor.h"

class Player : public Actor
{
public:
	void SetupComponents() override;
	void Update() override;
	void Destroy() override;

	void StopMoving();

	//for movement
	bool mIsMovingUp = false;
	bool mIsMovingDown = false;
	bool mIsMovingRight = false;
	bool mIsMovingLeft = false;

private:
	float mSpeedX = 100;
	float mSpeedY = 100;
};

