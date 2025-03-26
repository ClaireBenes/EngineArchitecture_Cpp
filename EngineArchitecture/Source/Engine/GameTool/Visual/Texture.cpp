#include "Texture.h"

#include "Engine/Renderer/IRenderer.h"
#include "Engine/Renderer/RendererSDL.h"
#include "Engine/Renderer/RendererGL.h"

//Load Texture
bool Texture::Load(IRenderer& pRenderer, const std::string& pFileName)
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

    if(pRenderer.GetType() == IRenderer::RendererType::SDL)
    {
        return LoadSDL(dynamic_cast<RendererSDL*>( &pRenderer ), pFileName, surface);
    }

    return LoadGL(dynamic_cast<RendererGL*>( &pRenderer ), pFileName, surface);
}

//Unload Texture
void Texture::Unload()
{
    if (mSDLTexture) 
    {
        SDL_DestroyTexture(mSDLTexture);
    }
    else
    {
        glDeleteTextures(1, &mTextureId);
    }
}

void Texture::SetActive() const
{
    glBindTexture(GL_TEXTURE_2D, mTextureId);
}

//Update width and height texture
void Texture::UpdateInfo(int& pWidthOut, int& pHeightOut)
{
    pWidthOut = mWidth;
    pHeightOut = mHeight;
}

//Get Texture Width
int Texture::GetWidth() const
{
	return mWidth;
}

//Get Texture Height
int Texture::GetHeight() const
{
	return mHeight;
}

SDL_Texture* Texture::GetSDLTexture() const
{
    return mSDLTexture;
}

bool Texture::LoadSDL(RendererSDL* pRenderer, const std::string& pFileName, SDL_Surface* pSurface)
{
    //Create texture from surface
    mSDLTexture = SDL_CreateTextureFromSurface(pRenderer->GetSDLRender(), pSurface);
    SDL_FreeSurface(pSurface);

    if(!mSDLTexture)
    {
        Log::Error(LogType::Render, "Failed to convert surface to texture :" + mFileName);
        return false;
    }

    Log::Info("Loaded SDL texture : " + mFileName);

    return true;
}

bool Texture::LoadGL(RendererGL* pRenderer, const std::string& pFileName, SDL_Surface* pSurface)
{
    int format = 0;

    if(pSurface->format->format == SDL_PIXELFORMAT_RGB24)
    {
        format = GL_RGB;
    }
    else if(pSurface->format->format == SDL_PIXELFORMAT_RGBA32)
    {
        format = GL_RGBA;
    }

    glGenTextures(1, &mTextureId);
    glBindTexture(GL_TEXTURE_2D, mTextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, pSurface->pixels);
    SDL_FreeSurface(pSurface);

    Log::Info("Loaded GL texture : " + mFileName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}
