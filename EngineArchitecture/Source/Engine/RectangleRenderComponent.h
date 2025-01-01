#pragma once

#include "RenderComponent.h"
#include "Rectangle.h"

class RectangleRenderComponent : public RenderComponent
{
public:
	void Render(Renderer* pRenderer) override;
	Rectangle mRectangle{Vector2(-16,-16),Vector2(32,32)};
};

