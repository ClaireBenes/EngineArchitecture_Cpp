#pragma once

#include "IRenderer.h"

#include <vector>

/**
 * @brief RendererSDL is an SDL-based renderer that implements IRenderer.
 * It manages the SDL rendering context, 
 * handles drawing 2D primitives (like rectangles), 
 * and textures (like sprites) using SDL's rendering functions.
*/
class RendererSDL : public IRenderer
{
public:
	/**
	 * @brief Constructor for RendererSDL.
	 * Initializes the SDL_Renderer to a nullptr.
	 */
	RendererSDL();

	// Deleted copy constructor and assignment operator to prevent copying.
	RendererSDL(const IRenderer&) = delete;
	IRenderer& operator= (const IRenderer&) = delete;

	/**
	 * @brief Initializes the SDL renderer with the specified window.
	 * @param rWindow The window to render the graphics onto.
	 * @return Returns true if initialization is successful, false otherwise.
	 */
	bool Initialize(Window& rWindow);
	/**
	 * @brief Begins the drawing process by setting the background color and clearing the screen.
	 */
	void BeginDraw() override;
	/**
	 * @brief Draws all render components to the screen.
	 */
	void Draw() override;
	/**
	 * @brief Ends the drawing process by presenting the rendered frame to the screen.
	 */
	void EndDraw() override;
	/**
	 * @brief Closes the SDL renderer and cleans up resources.
	 */
	void Close() override;

	/**
	 * @brief Gets the SDL_Renderer instance used by this renderer.
	 * @return The SDL_Renderer object.
	 */
	SDL_Renderer* GetSDLRender();

	/**
	 * @brief Draws a filled rectangle on the screen with the specified color.
	 * @param rRect The rectangle to be drawn.
	 * @param pColor The color of the rectangle.
	 */
	void DrawRect(const Rectangle& rRect, Color pColor) override;
	/*
	Draws the outline of a rectangle on the screen with the specified color.
	@param rRect The rectangle to be drawn.
	@param pColor The color of the rectangle outline.
	*/
	void DrawRectLine(const Rectangle& rRect, Color pColor) override;
	/**
	 * @brief Draws a sprite on the screen using the specified texture and transformation.
	 * @param rOwner The actor owning the sprite (used for context, not directly here).
	 * @param rTexture Pointer to the texture to render.
	 * @param rec The rectangle that defines the position and size of the sprite on screen.
	 * @param flip Specifies sprite flipping (horizontal, vertical, etc.).
	 */
	void DrawSprite(const Actor& rOwner, Texture* rTexture, Rectangle rec, Flip flip = Flip::None) override;

	/**
	 * @brief Gets the renderer type, which is SDL.
	 * @return RendererType::SDL.
	 */
	RendererType GetType() override;

private:
	/**
	 * @brief The SDL renderer instance.
	 */
	SDL_Renderer* mSdlRenderer; 
	/**
	 * @brief The background color of the screen.
	 */
	Color mBackgroundColor = { 120, 120, 255, 255 };
};


