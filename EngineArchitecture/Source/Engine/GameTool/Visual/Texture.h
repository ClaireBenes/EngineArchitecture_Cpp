#pragma once

#include <string>

#include "SDL_image.h"

class IRenderer;
class RendererGL;
class RendererSDL;

/*
Texture is a wrapper for SDL and OpenGL texture loading, management, and activation.
It abstracts differences between SDL and OpenGL renderers for texture creation and usage.
 */
class Texture
{
public:
	/*
	 * Loads a texture file using the appropriate renderer (SDL or OpenGL).
	 * @param pRenderer Reference to the renderer (determines backend).
	 * @param pFileName Path to the texture image file.
	 * @return True if the texture was successfully loaded, false otherwise.
	 */
	bool Load(IRenderer& pRenderer, const std::string& pFileName);
	/*
	 Frees resources associated with the texture.
	 */
	void Unload();
	/*
	 Binds the texture as the currently active OpenGL texture.
	 Note: This only applies to OpenGL renderers.
	 */
	void SetActive() const;

	/*
	 * Outputs the texture dimensions to the given references.
	 * @param pWidthOut Receives texture width.
	 * @param pHeightOut Receives texture height.
	 */
	void UpdateInfo(int& pWidthOut, int& pHeightOut); 

	//Getters & Setters

	/*
	 * Manually sets the size of the texture.
	 * @param width New width.
	 * @param height New height.
	 */
	void SetTextureSize(int width, int height);

	/*
	 * Gets the texture width.
	 * @return Width in pixels.
	 */
	int GetWidth() const;
	/*
	 * Gets the texture height.
	 * @return Height in pixels.
	 */
	int GetHeight() const;
	/*
	 * Gets the internal SDL texture pointer (only valid for SDL renderer).
	 * @return Pointer to SDL_Texture.
	 */
	SDL_Texture* GetSDLTexture() const;

private:
	std::string mFileName; // File path of the texture.
	SDL_Texture* mSDLTexture; // SDL texture pointer (only used by SDL renderer).

	int mWidth = 16; // Width of the texture in pixels.
	int mHeight = 16; // Height of the texture in pixels.

	unsigned int mTextureId; // OpenGL texture ID.

	/*
	 * Loads a texture using the SDL renderer.
	 * @param pRenderer Pointer to the SDL renderer.
	 * @param pFileName Path to the texture file.
	 * @param pSurface Loaded SDL surface.
	 * @return True on success.
	 */
	bool LoadSDL(RendererSDL* pRenderer, const std::string& pFileName, SDL_Surface* pSurface);
	/*
	 * Loads a texture using the OpenGL renderer.
	 * @param pRenderer Pointer to the OpenGL renderer.
	 * @param pFileName Path to the texture file.
	 * @param pSurface Loaded SDL surface.
	 * @return True on success.
	 */
	bool LoadGL(RendererGL* pRenderer, const std::string& pFileName, SDL_Surface* pSurface);
};

