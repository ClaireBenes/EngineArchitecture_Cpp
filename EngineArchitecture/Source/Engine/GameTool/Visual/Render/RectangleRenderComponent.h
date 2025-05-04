#pragma once

#include "RenderComponent.h"
#include "Engine/GameTool/Utility/Geometry/Rectangle.h"

/*
RectangleRenderComponent is a simple render component for drawing a 2D rectangle.
It renders in viewport space, making it suitable for UI or overlays.
 */
class RectangleRenderComponent : public RenderComponent
{
public:
	/*
	 * Renders the rectangle in screen space using the assigned color.
	 * Takes into account the owner's transform position.
	 * @param pRenderer Renderer interface for drawing the shape.
	 */
	void Render(IRenderer* pRenderer) override;
	/*
	 * Returns the rendering category (Viewport) for this rectangle component.
	 * @return RenderType::Viewport
	 */
	RenderType GetRenderType() override;

	// The local rectangle definition (position is relative to actor's transform).
	Rectangle mRectangle{Vector2(-16,-16),Vector2(32,32)};
};

