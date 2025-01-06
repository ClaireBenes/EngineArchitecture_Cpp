#pragma once

#include "Engine/GameTool/Actor.h"

class Player : public Actor
{
public:
	void SetupComponents() override;
	void Update() override;
	void Destroy() override;
};

