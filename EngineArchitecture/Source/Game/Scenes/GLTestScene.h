#pragma once

#include "Engine/GameTool/Scene.h"
#include "Engine/GameTool/Camera.h"

class GLTestScene : public Scene
{
public:
	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;

private:
	Camera* mCamera = nullptr;
};

