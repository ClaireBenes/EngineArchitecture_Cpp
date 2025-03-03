#pragma once

#include <string>

#include "SDL_image.h"

class RendererSDL;

class Texture
{
public:
	bool Load(RendererSDL& pRenderer, const std::string& pFileName);
	void Unload();

	void UpdateInfo(int& pWidthOut, int& pHeightOut); // Using references to get two informations out)

	int GetWidth() const;
	int GetHeight() const;
	SDL_Texture* GetSDLTexture() const;

private:
	std::string mFileName;
	SDL_Texture* mSDLTexture;

	int mWidth = 16;
	int mHeight = 16;
};

