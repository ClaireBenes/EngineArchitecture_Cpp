#pragma once
#include "SDL.h"

#include "Log.h"
#include "Vector2.h"

class Window
{
public:
	Window(int pWidth, int pHeight);
	Window(const Window&) = delete;

	Window& operator=(const Window&) = delete;
	Vector2 GetDimensions() const;
	SDL_Window* GetSdlWindow() const;

	bool Open();
	void Update();
	void Close();

private:
	Vector2 mDimensions = { 0,0 };
	SDL_Window* mSdlWindow;
};

