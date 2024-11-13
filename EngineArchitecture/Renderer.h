#pragma once

#include "Rectangle.h"
#include "Window.h"
#include "Vector4.h"

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

	void DrawRect(Rectangle& rRect, Color pColor);

private:
	//variables
	SDL_Renderer* mSdlRenderer;
	Color mBackgroundColor = { 120, 120, 255, 255 };

	
};


