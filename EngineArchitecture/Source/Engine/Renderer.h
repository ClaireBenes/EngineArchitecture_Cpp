#pragma once

#include "GameTool/Rectangle.h"
#include "GameTool/Vector/Vector4.h"
#include "Window.h"

class Actor;
class Texture;

class Renderer
{
public:
	Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator= (const Renderer&) = delete;

	//function
	bool Initialize(Window& rWindow);
	void BeginDraw();
	void EndDraw();
	void Close();

	SDL_Renderer* GetSDLRender();

	void DrawRect(const Rectangle& rRect, Color pColor);
	void DrawRectLine(const Rectangle& rRect, Color pColor);
	void DrawSprite(Texture& pTex, const Rectangle& rRect, Actor* pOwner) const;

private:
	//variables
	SDL_Renderer* mSdlRenderer;
	Color mBackgroundColor = { 120, 120, 255, 255 };
	
};


