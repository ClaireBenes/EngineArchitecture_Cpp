#pragma once

#include "../RenderComponent.h"

#include "Engine/GameTool/Visual/Texture.h"
#include "Engine/GameTool/Utility/Geometry/Rectangle.h"

#include "Engine/Renderer/IRenderer.h"

/*
SpriteRenderComponent is responsible for rendering textured 2D sprites.
It operates in viewport space and is ideal for UI elements or 2D graphics.
Supports draw ordering, flipping, and customizable rectangle dimensions.
 */
class SpriteRenderComponent : public RenderComponent
{
public:
	/*
	 * Constructs a sprite render component without a texture.
	 * @param pOwner The actor that owns this component.
	 * @param pDrawOrder The drawing order priority (higher values draw later).
	 */
	SpriteRenderComponent(Actor* pOwner, int pDrawOrder = 100);
	/*
	 * Constructs a sprite render component with an initial texture.
	 * @param pOwner The actor that owns this component.
	 * @param pTexture The texture to be rendered.
	 * @param pDrawOrder The drawing order priority.
	 */
	SpriteRenderComponent(Actor* pOwner, Texture* pTexture, int pDrawOrder = 100);

	// Deleted constructors and assignment operators to enforce non-copyable behavior.
	SpriteRenderComponent() = delete;
	SpriteRenderComponent(const SpriteRenderComponent&) = delete;
	SpriteRenderComponent& operator= (const SpriteRenderComponent&) = delete;

	/*
	 * Sets or updates the texture used by this sprite.
	 * Also updates internal texture dimensions.
	 * @param pTexture Pointer to the new texture.
	 */
	virtual void SetTexture(Texture* pTexture);
	/*
	 * Renders the sprite using the provided renderer.
	 * Applies flip settings and position based on the rectangle.
	 * @param pRenderer The renderer used for drawing.
	 */
	virtual void Render(IRenderer* pRenderer) override;
	/*
	 * Returns the render type of this component (Viewport).
	 * @return RenderType::Viewport
	 */
	RenderType GetRenderType() override;

	/*
	 * Sets new dimensions (width and height) for the sprite's rectangle.
	 * @param x Width of the sprite.
	 * @param y Height of the sprite.
	 */
	void SetNewDimensions(float x, float y);
	/*
	 * Sets a new position (x, y) for the sprite's rectangle.
	 * @param x X-position of the sprite.
	 * @param y Y-position of the sprite.
	 */
	void SetNewPositions(float x, float y);

	//Getters

	/*
	 * Gets the drawing order priority of this component.
	 * Higher values render on top of lower values.
	 * @return Drawing order priority.
	 */
	int GetDrawOrder() const override;
	/*
	 * Gets the width of the texture used by this sprite.
	 * @return Texture width in pixels.
	 */
	int GetTexWidth() const;
	/*
	 * Gets the height of the texture used by this sprite.
	 * @return Texture height in pixels.
	 */
	int GetTexHeight() const;

public:
	// The rectangle defining sprite position and size, relative to the actor.
	Rectangle mRectangle{ Vector2(-16,-16),Vector2(32,32) };
	// Flip mode (none, horizontal, vertical, both) for sprite rendering.
	IRenderer::Flip mFlip = IRenderer::Flip::None;

protected:
	// The texture used for rendering this sprite.
	Texture* mTexture;

	int mDrawOrder; // Drawing order priority.
	int mTexWidth; // Internal texture width (updated with SetTexture).
	int mTexHeight; // Internal texture height (updated with SetTexture).
};

