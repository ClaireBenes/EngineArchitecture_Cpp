#include "RendererSDL.h"

#include "SDL_image.h"

#include "Engine/Window.h"
#include "Engine/GameTool/Actor.h"
#include "Engine/GameTool/Utility/Maths.h"
#include "Engine/GameTool/Visual/Texture.h"
#include "Engine/GameTool/Visual/Render/Sprite/SpriteRenderComponent.h"

RendererSDL::RendererSDL() : mSdlRenderer(nullptr)
{
}

IRenderer::RendererType RendererSDL::GetType()
{
    return RendererType::SDL;
}


//Initialize renderer
bool RendererSDL::Initialize(Window& rWindow)
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
void RendererSDL::BeginDraw()
{
    //Background Color
    SDL_SetRenderDrawColor(mSdlRenderer, static_cast<Uint8>(mBackgroundColor.x), static_cast<Uint8>(mBackgroundColor.y), 
        static_cast<Uint8>(mBackgroundColor.z), static_cast<Uint8>(mBackgroundColor.w));
    SDL_RenderClear(mSdlRenderer);
}

//End Draw
void RendererSDL::EndDraw()
{
    SDL_RenderPresent(mSdlRenderer);
}

//Close Game
void RendererSDL::Close()
{
    SDL_DestroyRenderer(mSdlRenderer);
}

SDL_Renderer* RendererSDL::GetSDLRender()
{
    return mSdlRenderer;
}

//Draw Rectangle
void RendererSDL::DrawRect(const Rectangle& rRect, Color pColor)
{
    SDL_SetRenderDrawColor(mSdlRenderer, static_cast<Uint8>(pColor.x), static_cast<Uint8>(pColor.y), static_cast<Uint8>(pColor.z), static_cast<Uint8>(pColor.w));
    SDL_Rect sdlRect = rRect.ToSdlRect();
    SDL_RenderFillRect(mSdlRenderer, &sdlRect);
}

void RendererSDL::DrawRectLine(const Rectangle& rRect, Color pColor)
{
    SDL_SetRenderDrawColor(mSdlRenderer, static_cast< Uint8 >( pColor.x ), static_cast< Uint8 >( pColor.y ), static_cast< Uint8 >( pColor.z ), static_cast< Uint8 >( pColor.w ));
    SDL_Rect sdlRect = rRect.ToSdlRect();
    SDL_RenderDrawRect(mSdlRenderer, &sdlRect);
}

void RendererSDL::DrawSprite(const Actor& rOwner, Texture& rTexture, Rectangle rec, Flip flip)
{
    SDL_Rect destinationRect;
    Transform transform = *rOwner.mTransform;
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
            Maths::Round(static_cast<float>(rTexture.GetWidth())),
            Maths::Round(static_cast<float>(rTexture.GetHeight()))
        };
    }

    SDL_RenderCopyEx(mSdlRenderer,
        rTexture.GetSDLTexture(),
        sourceSDL,
        &destinationRect,
        -Maths::ToDeg(transform.mRotation.z),
        nullptr,
        static_cast<SDL_RendererFlip>(flip));

    delete sourceSDL;
}

void RendererSDL::AddSprite(SpriteRenderComponent* pSprite)
{
    int spriteDrawOrder = pSprite->GetDrawOrder();
    std::vector<SpriteRenderComponent*>::iterator spriteIterator;

    for(spriteIterator = mSprites.begin(); spriteIterator != mSprites.end(); ++spriteIterator)
    {
        if(spriteDrawOrder < ( *spriteIterator )->GetDrawOrder()) break;
    }
    mSprites.insert(spriteIterator, pSprite);
}

void RendererSDL::RemoveSprite(SpriteRenderComponent* pSprite)
{
    std::vector<SpriteRenderComponent*>::iterator spriteIterator;
    spriteIterator = std::find(mSprites.begin(), mSprites.end(), pSprite);
    mSprites.erase(spriteIterator);
}


