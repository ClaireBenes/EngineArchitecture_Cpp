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
	static constexpr int GridWidth = 30;
	static constexpr int GridHeight = 30;

	static constexpr int VerticesCountX = 100;
	static constexpr int VerticesCountY = 100;

private:
	Camera* mCamera = nullptr;
	EditorController* mMoveComponent = nullptr;

	// Need to use Vector4 (instead of Vec3) cause OpenGL force the stride at 16 bytes instead of 12 for buffers.
	std::vector<Vector4> mVertices {};

	unsigned int mVertexArrayId = 0;

	// Double buffering with an index to swap them
	unsigned int mDoubleBufferIndex = 0;
	unsigned int mPositionBuffers[2] {};
	unsigned int mVelocityBuffers[2] {};

	ShaderProgram mComputeShader;
	ShaderProgram mRenderShader;
};

