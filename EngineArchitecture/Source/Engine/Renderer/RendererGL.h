#pragma once

#include "IRenderer.h"
#include "Engine/Vertex/VertexArray.h"

#include <vector>

class RendererGL : public IRenderer
{
public:
	RendererGL();
	virtual ~RendererGL();
	RendererGL(const RendererGL&) = delete;
	RendererGL& operator=(const RendererGL&) = delete;

	bool Initialize(Window& rWindow) override;
	void BeginDraw() override;
	void EndDraw() override;

	void DrawSprite(const Actor& rOwner, Texture& rTexture, Rectangle rec, Flip flip = Flip::None) const override {};
	void AddSprite(SpriteRenderComponent* pSprite) override;
	void RemoveSprite(SpriteRenderComponent* pSprite) override;

	void Close() override;
	RendererType GetType() override;

private:
	Window* mWindow;
	VertexArray* mVao;
	SDL_GLContext mContext;
	std::vector<SpriteRenderComponent*> mSprites;
};


