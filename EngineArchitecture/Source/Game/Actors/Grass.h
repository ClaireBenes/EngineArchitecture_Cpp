#pragma once

#include "Engine/GameTool/Actor.h"

class Mesh;

class Grass : public Actor
{
public:
	void Start() override;
	void SetupComponents() override;
};

