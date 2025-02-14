#pragma once

#include "GameTool/Rectangle.h"
#include "GameTool/Vector/Vector4.h"
#include "Window.h"

#include <vector>

class Actor;
class Texture;
class SpriteRenderComponent;

class Renderer
{
public:
	Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator= (const Renderer&) = delete;

	//to wrap SDL sprites flipping modes
	enum class Flip
	{
		None = SDL_FLIP_NONE,
		Horizontal = SDL_FLIP_HORIZONTAL,
		Vertical = SDL_FLIP_VERTICAL
	};


	//function
	bool Initialize(Window& rWindow);
	void BeginDraw();
	void EndDraw();
	void Close();

	SDL_Renderer* GetSDLRender();

	void DrawRect(const Rectangle& rRect, Color pColor);
	void DrawRectLine(const Rectangle& rRect, Color pColor);
	void DrawSprite(const Actor& rOwner, Texture& rTexture, Rectangle rec, Flip flip) const;

	void AddSprite(SpriteRenderComponent* pSprite);
	void RemoveSprite(SpriteRenderComponent* pSprite);

private:
	//variables
	SDL_Renderer* mSdlRenderer;
	Color mBackgroundColor = { 120, 120, 255, 255 };

	std::vector<SpriteRenderComponent*> mSprites;
	
};


