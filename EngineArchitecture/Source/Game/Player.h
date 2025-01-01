#pragma once

#include "Engine/Actor.h"

class Player : public Actor
{
public:
	void SetupComponents() override;
	void Update() override;
	void Destroy() override;
};

