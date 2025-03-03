#pragma once

#include "Engine/GameTool/Scene.h"

class GLTestScene : public Scene
{
public:
	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;
};

