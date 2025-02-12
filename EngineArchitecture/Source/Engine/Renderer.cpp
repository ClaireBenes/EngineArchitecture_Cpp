#include "Renderer.h"

#include "SDL_image.h"

#include "GameTool/Actor.h"
#include "GameTool/Utility/Math.h"
#include "GameTool/Visual/Texture.h"

Renderer::Renderer() : mSdlRenderer(nullptr)
{
}

//Initialize renderer
bool Renderer::Initialize(Window& rWindow)
{
    mSdlRenderer = SDL_CreateRenderer(rWindow.GetSdlWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!mSdlRenderer)
    {
        Log::Error(LogType::Video, "Failed to create Renderer");
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        Log::Error(LogType::Video, "Unable to initialize SDL_Image");
        return false;
    }

    return true;
}

//Draw
void Renderer::BeginDraw()
{
    //Background Color
    SDL_SetRenderDrawColor(mSdlRenderer, static_cast<Uint8>(mBackgroundColor.x), static_cast<Uint8>(mBackgroundColor.y), 
        static_cast<Uint8>(mBackgroundColor.z), static_cast<Uint8>(mBackgroundColor.w));
    SDL_RenderClear(mSdlRenderer);
}

//End Draw
void Renderer::EndDraw()
{
    SDL_RenderPresent(mSdlRenderer);
}

//Close Game
void Renderer::Close()
{
    SDL_DestroyRenderer(mSdlRenderer);
}

SDL_Renderer* Renderer::GetSDLRender()
{
    return mSdlRenderer;
}

//Draw Rectangle
void Renderer::DrawRect(const Rectangle& rRect, Color pColor)
{
    SDL_SetRenderDrawColor(mSdlRenderer, static_cast<Uint8>(pColor.x), static_cast<Uint8>(pColor.y), static_cast<Uint8>(pColor.z), static_cast<Uint8>(pColor.w));
    SDL_Rect sdlRect = rRect.ToSdlRect();
    SDL_RenderFillRect(mSdlRenderer, &sdlRect);
}

void Renderer::DrawRectLine(const Rectangle& rRect, Color pColor)
{
    SDL_SetRenderDrawColor(mSdlRenderer, static_cast< Uint8 >( pColor.x ), static_cast< Uint8 >( pColor.y ), static_cast< Uint8 >( pColor.z ), static_cast< Uint8 >( pColor.w ));
    SDL_Rect sdlRect = rRect.ToSdlRect();
    SDL_RenderDrawRect(mSdlRenderer, &sdlRect);
}

void Renderer::DrawSprite(Texture& pTex, const Rectangle& rRect, Actor* pOwner) const
{
    SDL_Rect sdlRect = rRect.ToSdlRect();

    SDL_Rect* sourceSDL = nullptr;
    if (rRect != Rectangle::NullRect)
    {
        sourceSDL = new SDL_Rect{
            Maths::Round(rRect.position.x),
            Maths::Round(rRect.position.y),
            Maths::Round(rRect.dimensions.x),
            Maths::Round(rRect.dimensions.y) };
    }

    SDL_RenderCopyEx(mSdlRenderer,
        pTex.GetSDLTexture(),
        sourceSDL,
        &sdlRect,
        -Maths::ToDeg(pOwner->mTransform.mRotation),
        nullptr,
        SDL_FLIP_NONE);

    delete sourceSDL;

}



