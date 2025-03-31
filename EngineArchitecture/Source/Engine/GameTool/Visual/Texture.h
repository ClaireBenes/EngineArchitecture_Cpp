#pragma once

#include <string>

#include "SDL_image.h"

class IRenderer;
class RendererGL;
class RendererSDL;

class Texture
{
public:
	bool Load(IRenderer& pRenderer, const std::string& pFileName);
	void Unload();
	void SetActive() const;

	void UpdateInfo(int& pWidthOut, int& pHeightOut); 

	//Getters & Setters
	void SetTextureSize(int width, int height);

	int GetWidth() const;
	int GetHeight() const;
	SDL_Texture* GetSDLTexture() const;

private:
	std::string mFileName;
	SDL_Texture* mSDLTexture;

	int mWidth = 16;
	int mHeight = 16;

	unsigned int mTextureId;

	bool LoadSDL(RendererSDL* pRenderer, const std::string& pFileName, SDL_Surface* pSurface);
	bool LoadGL(RendererGL* pRenderer, const std::string& pFileName, SDL_Surface* pSurface);
};

