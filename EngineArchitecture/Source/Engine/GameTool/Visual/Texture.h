#pragma once

#include <string>

#include "SDL_image.h"

class Renderer;

class Texture
{
public:
	bool Load(Renderer& pRenderer, const std::string& pFileName);
	void Unload();

	void UpdateInfo(int& pWidthOut, int& pHeightOut); // Using references to get two informations out)

	int GetWidth();
	int GetHeight();
	SDL_Texture* GetSDLTexture();

private:
	std::string mFileName;
	SDL_Texture* mSDLTexture;

	int mWidth = 16;
	int mHeight = 16;
};

