#pragma once

#include "IRenderer.h"

#include <vector>

class RendererSDL : public IRenderer
{
public:
	RendererSDL();
	RendererSDL(const IRenderer&) = delete;
	IRenderer& operator= (const IRenderer&) = delete;

	//function
	bool Initialize(Window& rWindow);
	void BeginDraw() override;
	void Draw() override;
	void EndDraw() override;
	void Close() override;

	SDL_Renderer* GetSDLRender();

	void DrawRect(const Rectangle& rRect, Color pColor) override;
	void DrawRectLine(const Rectangle& rRect, Color pColor) override;
	void DrawSprite(const Actor& rOwner, Texture& rTexture, Rectangle rec, Flip flip = Flip::None) override;

	RendererType GetType() override;

private:
	//variables
	SDL_Renderer* mSdlRenderer;
	Color mBackgroundColor = { 120, 120, 255, 255 };
};


