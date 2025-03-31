#pragma once

#include "Actor.h"

class Camera : public Actor
{
public:
	void SetupComponents() override {};
	void Update() override;
};

