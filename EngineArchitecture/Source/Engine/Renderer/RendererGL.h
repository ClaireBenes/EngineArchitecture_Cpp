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
	void EndDraw() override;

	void DrawRect(const Rectangle& rRect, Color pColor) override;
	void DrawRectLine(const Rectangle& rRect, Color pColor) override;

	void DrawSprite(const Actor& rOwner, Texture& rTexture, Rectangle rec, Flip flip = Flip::None) override;
	void AddSprite(SpriteRenderComponent* pSprite) override;
	void RemoveSprite(SpriteRenderComponent* pSprite) override;

	void Close() override;
	RendererType GetType() override;

private:
	Window* mWindow;
	VertexArray* mVao;
	SDL_GLContext mContext;
	std::vector<SpriteRenderComponent*> mSprites;

	//SHADERS
	//Sprite
	Shader mSpriteFragShader;
	Shader mSpriteVertexShader;
	//Rect
	Shader mRectFragShader;
	Shader mRectVertexShader;
	//RectLine
	Shader mRectLineFragShader;
	Shader mRectLineVertexShader;

	//ShaderProgram
	ShaderProgram mSpriteShaderProgram;
	ShaderProgram mRectShaderProgram;
	ShaderProgram mRectLineShaderProgram;
};


