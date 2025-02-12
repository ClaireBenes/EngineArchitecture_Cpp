#pragma once
#include "SDL.h"

#include "Log.h"
#include "GameTool/Vector/Vector2.h"

class Window
{
public:
	Window(int pWidth, int pHeight, std::string pTitle);
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	//functions
	Vector2 GetDimensions() const;
	SDL_Window* GetSdlWindow() const;

	bool Open();
	void Update();
	void Close();

private:
	//variables
	Vector2 mDimensions = { 0,0 };
	SDL_Window* mSdlWindow;
	std::string mTitle = "Best Game";
};

