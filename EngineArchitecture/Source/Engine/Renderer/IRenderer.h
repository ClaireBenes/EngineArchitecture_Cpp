#pragma once

#include "Engine/GameTool/Utility/Geometry/Rectangle.h"
#include "Engine/GameTool/Utility/Vector/Vector4.h"
#include "Engine/GameTool/Utility/Matrix/Matrix4.h"
#include "Engine/Window.h"

#include <vector>

class Actor;
class Texture;
class Mesh;
class RenderComponent;
class DebugRenderInterface;

/**
 * @brief IRenderer is an abstract base class for rendering systems. It defines methods for
 * initializing, drawing, and managing graphics resources, which must be implemented
 * by specific renderer classes (e.g., OpenGL, SDL).
*/
class IRenderer
{
public:

    /**
     * @brief Enum to represent the different flipping modes for rendering sprites.
     * This allows flipping a sprite horizontally or vertically, or no flipping at all.
     */
    enum class Flip
    {
        None = SDL_FLIP_NONE,
        Horizontal = SDL_FLIP_HORIZONTAL,
        Vertical = SDL_FLIP_VERTICAL
    };

    /**
     * @brief Enum representing the type of renderer (either SDL or OpenGL).
     * This helps identify which underlying rendering system is being used.
     */
    enum class RendererType
    {
        SDL,
        OPENGL
    };

    // Destructor for IRenderer
    virtual ~IRenderer() = default;

    /**
     * @brief Initializes the renderer with the provided window.
     * @param rWindow The window that the renderer will be associated with.
     * @return True if the initialization was successful, false otherwise.
     */
    virtual bool Initialize(Window& rWindow) = 0;
    /**
     * @brief Prepares for drawing, called before rendering starts.
     */
    virtual void BeginDraw() = 0;
    /**
     * @brief Draws the rendered objects to the screen.
     * This should be called after all draw calls have been issued.
     */
    virtual void Draw() = 0;
    /**
     * @briefCompletes the drawing process.
     */
    virtual void EndDraw() = 0;
    /**
     * @brief Closes the renderer and releases any allocated resources.
     */
    virtual void Close() = 0;

    /**
     * @brief Gets the type of the renderer being used.
     * @return The renderer type (SDL or OpenGL).
     */
    virtual RendererType GetType() = 0;

    /**
     * @brief Draws a filled rectangle on the screen.
     * @param rRect The rectangle defining the position and size of the rectangle.
     * @param pColor The color of the rectangle.
     */
    virtual void DrawRect(const Rectangle& rRect, Color pColor) = 0;
    /**
     * @brief Draws only the outline (border) of a rectangle on the screen.
     * @param rRect The rectangle defining the position and size of the rectangle.
     * @param pColor The color of the rectangle's border.
     */
    virtual void DrawRectLine(const Rectangle& rRect, Color pColor) = 0;

    /**
     * @brief Draws a 2D sprite on the screen using the provided texture and rectangle.
     * @param rOwner The owning actor of the sprite (used for context, not directly here).
     * @param rTexture Pointer to the texture to render.
     * @param rec Defines the position and size of the sprite on screen.
     * @param flip Specifies sprite flipping (horizontal, vertical, etc.).
     */
    virtual void DrawSprite(const Actor& rOwner, Texture* rTexture, Rectangle rec, Flip flip = Flip::None) = 0;

    /**
     * @brief Draws a mesh with a specific texture index and transformation.
    * @param pMesh The mesh to be drawn.
    * @param pTextureIndex Index of the mesh's texture to use.
    * @param transform World transformation matrix.
    * @param tiling Texture tiling to apply.
    */ 
    virtual void DrawMesh(Mesh* pMesh, int pTextureIndex, const Matrix4& transform, Vector2 tiling = Vector2::ONE) {};

    /**
     * @brief Adds a render component to the list of components to be rendered.
     * @param pRenderComponent The render component to be added.
     */
    void AddRenderComponent(RenderComponent* pRenderComponent);
    /**
     * @brief Removes a render component from the list of components to be rendered.
     * @param pRenderComponent The render component to be removed.
     */
    void RemoveRenderComponent(RenderComponent* pRenderComponent);

    /**
     * @brief Adds a debug render component to the renderer.
     * @param pDebugRender The debug render interface to be added.
     */
    void AddDebugRender(DebugRenderInterface* pDebugRender);
    /**
     * @brief Removes a debug render component from the renderer.
     * @param pDebugRender The debug render interface to be removed.
     */
    void RemoveDebugRender(DebugRenderInterface* pDebugRender);

    /**
     * @brief Sets the view matrix for the renderer.
     * This is usually used for camera transformations.
     * @param pView The view transformation matrix (e.g., camera position and orientation).
     */
    virtual void SetViewMatrix(const Matrix4& pView) {};

    /**
     * TODO
     */
    virtual const Matrix4& GetViewMatrix() { return Matrix4::Identity; };
    /**
     * TODO
     */
    virtual const Matrix4& GetProjectionMatrix() { return Matrix4::Identity; };

protected:
    /**
     * @brief List of render components associated with the viewport
     */
    std::vector<RenderComponent*> mViewportRenderComponents;
    /**
     * @brief List of render components associated with the world (3D space)
     */
    std::vector<RenderComponent*> mWorldRenderComponents; 
    /**
     * @brief List of debug render components
     */
    std::vector<DebugRenderInterface*> mDebugRenders;
};


