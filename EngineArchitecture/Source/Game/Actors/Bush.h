#pragma once

#include "Engine/GameTool/Actor.h"

class Bush : public Actor
{
public:
	void SetupComponents() override;
	void Update() override;
	void Destroy() override;
};

