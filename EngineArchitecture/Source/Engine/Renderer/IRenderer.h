#pragma once

#include "Engine/GameTool/Rectangle.h"
#include "Engine/GameTool/Utility/Vector/Vector4.h"
#include "Engine/Window.h"

class Actor;
class Texture;
class SpriteRenderComponent;

class IRenderer
{
public:
    //to wrap SDL sprites flipping modes
    enum class Flip
    {
        None = SDL_FLIP_NONE,
        Horizontal = SDL_FLIP_HORIZONTAL,
        Vertical = SDL_FLIP_VERTICAL
    };

    enum class RendererType
    {
        SDL,
        OPENGL
    };

    virtual ~IRenderer() = default;

    virtual bool Initialize(Window& rWindow) = 0;
    virtual void BeginDraw() = 0;
    virtual void EndDraw() = 0;
    virtual void Close() = 0;
    virtual RendererType GetType() = 0;

    virtual void AddSprite(SpriteRenderComponent* pSprite) = 0;
    virtual void RemoveSprite(SpriteRenderComponent* pSprite) = 0;
    virtual void DrawSprite(const Actor& rOwner, Texture& rTexture, Rectangle rec, Flip flip = Flip::None) const = 0;
};


