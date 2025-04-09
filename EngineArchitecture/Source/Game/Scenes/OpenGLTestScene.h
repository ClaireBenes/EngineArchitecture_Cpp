#pragma once

#include "Engine/GameTool/Scene.h"

class Mesh;
class Camera;
class EditorController;

class OpenGLTestScene : public Scene
{
public:
	void Load() override;
	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;

private:
	Mesh* mFloorMesh = nullptr;
	Mesh* mGrassMesh = nullptr;

	Camera* mCamera = nullptr;
	EditorController* mMoveComponent = nullptr;
};

