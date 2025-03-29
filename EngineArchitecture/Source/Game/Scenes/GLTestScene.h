#pragma once

#include "Engine/GameTool/Scene.h"
#include "Engine/GameTool/Camera.h"

class Mesh;

class GLTestScene : public Scene
{
public:
	void Load() override;
	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;

private:
	Camera* mCamera = nullptr;
	Mesh* mPinMesh = nullptr;
	Mesh* mFloorMesh = nullptr;
	Mesh* mBall = nullptr;
};

