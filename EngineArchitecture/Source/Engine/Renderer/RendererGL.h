#pragma once

#include "IRenderer.h"
#include "Engine/Vertex/VertexArray.h"
#include "Engine/Shader/ShaderProgram.h"

#include <vector>

class RendererGL : public IRenderer
{
public:
	RendererGL();
	virtual ~RendererGL();
	RendererGL(const RendererGL&) = delete;
	RendererGL& operator=(const RendererGL&) = delete;

	bool Initialize(Window& rWindow) override;
	void LoadShaders();
	void BeginDraw() override;
	void Draw() override;
	void EndDraw() override;

	void DrawRect(const Rectangle& rRect, Color pColor) override;
	void DrawRectLine(const Rectangle& rRect, Color pColor) override;

	void DrawAllSprites();
	void DrawSprite(const Actor& rOwner, Texture* rTexture, Rectangle rec, Flip flip = Flip::None) override;

	void DrawAllMeshes();
	void DrawMesh(Mesh* pMesh, int pTextureIndex, const Matrix4& transform, Vector2 tiling = Vector2::ONE) override;

	void SetViewMatrix(const Matrix4& pView) override;

	void Close() override;
	RendererType GetType() override;

	static Mesh* GetCubeMesh();
	static ShaderProgram mSimpleMeshShaderProgram;
	static ShaderProgram mTesselationMeshShaderProgram;
	static ShaderProgram mGrassShaderProgram;

private:
	Window* mWindow;
	VertexArray* mSpriteVao;
	SDL_GLContext mContext;

	Matrix4 mSpriteViewProj;
	Matrix4 mView;
	Matrix4 mProjection;

	static Mesh* mCubeMesh;

	//ShaderProgram
	ShaderProgram mSpriteShaderProgram;
	ShaderProgram mRectShaderProgram;
	ShaderProgram mRectLineShaderProgram;	
	ShaderProgram mTerrainShaderProgram;
};


