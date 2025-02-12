#include "Texture.h"

#include "SDL_image.h"

//Load Texture
bool Texture::Load(Renderer& pRenderer, const std::string& pFileName)
{
    mFileName = pFileName;
    SDL_Surface* surface = IMG_Load(mFileName.c_str());
    if (!surface)
    {
        Log::Error(LogType::Application, "Failed to load texture file :" + mFileName);
        return false;
    }
    mWidth = surface->w;
    mHeight = surface->h;

    //Create texture from surface
    mSDLTexture = SDL_CreateTextureFromSurface(pRenderer.GetSDLRender(), surface);
    SDL_FreeSurface(surface);
    if (!mSDLTexture)
    {
        Log::Error(LogType::Render, "Failed to convert surface to texture :" + mFileName);
        return false;
    }
    Log::Info("Loaded texture : " + mFileName);
    return true;
}

//Unload Texture
void Texture::Unload()
{
    if (mSDLTexture) 
    {
        SDL_DestroyTexture(mSDLTexture);
    }
}

//Update width and height texture
void Texture::UpdateInfo(int& pWidthOut, int& pHeightOut)
{
    pWidthOut = mWidth;
    pHeightOut = mHeight;
}

//Get Texture Width
int Texture::GetWidth()
{
	return mWidth;
}

//Get Texture Height
int Texture::GetHeight()
{
	return mHeight;
}

SDL_Texture* Texture::GetSDLTexture()
{
    return mSDLTexture;
}
