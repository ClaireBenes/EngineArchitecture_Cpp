#pragma once

#include "Engine/GameTool/Rectangle.h"
#include "Engine/GameTool/Utility/Vector/Vector4.h"
#include "Engine/GameTool/Utility/Matrix/Matrix4.h"
#include "Engine/Window.h"

#include <vector>

class Actor;
class Texture;
class Mesh;
class RenderComponent;

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
    virtual void Draw() = 0;
    virtual void EndDraw() = 0;
    virtual void Close() = 0;
    virtual RendererType GetType() = 0;

    virtual void DrawRect(const Rectangle& rRect, Color pColor) = 0;
    virtual void DrawRectLine(const Rectangle& rRect, Color pColor) = 0;

    virtual void DrawSprite(const Actor& rOwner, Texture& rTexture, Rectangle rec, Flip flip = Flip::None) = 0;
    virtual void DrawMesh(Mesh* pMesh, int pTextureIndex, const Matrix4& transform) {};

    virtual void AddRenderComponent(RenderComponent* pRenderComponent);
    virtual void RemoveRenderComponent(RenderComponent* pRenderComponent);

    virtual void SetViewMatrix(const Matrix4& pView) {};

protected:
    std::vector<RenderComponent*> mViewportRenderComponents;
    std::vector<RenderComponent*> mWorldRenderComponents;
};


