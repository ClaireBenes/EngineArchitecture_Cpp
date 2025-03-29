#pragma once

#include "Engine/GameTool/Actor.h"

class BowlingBall : public Actor
{
public:
	void Start() override;
	void SetupComponents() override;
	void Update() override;
};

