#pragma once

#include "Engine/GameTool/Actor.h"

class Wall : public Actor
{
	void SetupComponents() override;
	void Update() override;
	void Destroy() override;
};

