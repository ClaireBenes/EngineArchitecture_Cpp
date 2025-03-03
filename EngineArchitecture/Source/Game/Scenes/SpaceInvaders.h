#pragma once

#include "Engine/GameTool/Scene.h"

class Player;

class SpaceInvaders : public Scene
{
public:
	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;

private:
	Player* player = nullptr;
};

