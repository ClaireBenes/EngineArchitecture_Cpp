#pragma once

#include "Engine/GameTool/Scene.h"

class Player;

class Platformer2D : public Scene
{
public:
	void Start() override;
	void Update(float deltaTime) override;

private:
	Player* player = nullptr;
};

