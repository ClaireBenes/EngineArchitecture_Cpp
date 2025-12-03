#pragma once

#include "Engine/GameTool/Scene.h"
#include "Engine/Shader/ShaderProgram.h"

class Camera;
class EditorController;

class ComputeShader : public Scene
{
public:
	void Load() override;
	void Start() override;

	void Update(float deltaTime) override;
	void Draw() override;

private:
	static constexpr int GridWidth = 50;
	static constexpr int GridHeight = 50;

	static constexpr int VerticesCountX = 100;
	static constexpr int VerticesCountY = 100;

private:
	Camera* mCamera = nullptr;
	EditorController* mMoveComponent = nullptr;

	std::vector<Vector3> mVertices {};

	unsigned int mVertexArrayId = 0;
	unsigned int mVertexBufferId = 0;

	ShaderProgram mComputeShader;
	ShaderProgram mRenderShader;
};

