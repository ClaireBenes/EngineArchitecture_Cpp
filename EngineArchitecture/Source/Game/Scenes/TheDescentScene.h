#pragma once

#include "Engine/GameTool/Scene.h"

class TheDescentPlayer;

class TheDescentScene : public Scene
{
public:
	void Load() override;
	void Start() override;
	void Update(float deltaTime) override;

private:
	TheDescentPlayer* mPlayer = nullptr;
};

