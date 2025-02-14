#include "Renderer.h"

#include "SDL_image.h"

#include "Window.h"
#include "GameTool/Actor.h"
#include "GameTool/Utility/Math.h"
#include "GameTool/Visual/Texture.h"
#include "GameTool/Visual/Render/Sprite/SpriteRenderComponent.h"

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

void Renderer::DrawSprite(const Actor& rOwner, Texture& rTexture, Rectangle rec, Flip flip) const
{
    SDL_Rect destinationRect;
    Transform2D transform = rOwner.mTransform;
    destinationRect.w = static_cast< int >( transform.mScale.x * rec.dimensions.x);
    destinationRect.h = static_cast< int >( transform.mScale.y * rec.dimensions.y);
    destinationRect.x = static_cast< int >( rec.position.x);
    destinationRect.y = static_cast< int >( rec.position.y);

    SDL_Rect* sourceSDL = nullptr;
    if(rec != Rectangle::NullRect)
    {
        sourceSDL = new SDL_Rect
        {
            Maths::Round(0),
            Maths::Round(0),
            Maths::Round(rTexture.GetWidth()),
            Maths::Round(rTexture.GetHeight())
        };
    }

    SDL_RenderCopyEx(mSdlRenderer,
        rTexture.GetSDLTexture(),
        sourceSDL,
        &destinationRect,
        -Maths::ToDeg(transform.mRotation),
        nullptr,
        static_cast<SDL_RendererFlip>(flip));

    delete sourceSDL;
}

void Renderer::AddSprite(SpriteRenderComponent* pSprite)
{
    int spriteDrawOrder = pSprite->GetDrawOrder();
    std::vector<SpriteRenderComponent*>::iterator spriteIterator;

    for(spriteIterator = mSprites.begin(); spriteIterator != mSprites.end(); ++spriteIterator)
    {
        if(spriteDrawOrder < ( *spriteIterator )->GetDrawOrder()) break;
    }
    mSprites.insert(spriteIterator, pSprite);
}

void Renderer::RemoveSprite(SpriteRenderComponent* pSprite)
{
    std::vector<SpriteRenderComponent*>::iterator spriteIterator;
    spriteIterator = std::find(mSprites.begin(), mSprites.end(), pSprite);
    mSprites.erase(spriteIterator);
}



