#pragma once

#include "Engine/GameTool/Actor.h"

class Mesh;

class Pin : public Actor
{
public:
	void Start() override;
	void SetupComponents() override;
	void Update() override;
};

