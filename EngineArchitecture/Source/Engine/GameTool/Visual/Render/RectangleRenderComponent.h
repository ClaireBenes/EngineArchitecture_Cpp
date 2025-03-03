#pragma once

#include "RenderComponent.h"
#include "../../Rectangle.h"

//Rectangle
class RectangleRenderComponent : public RenderComponent
{
public:
	void Render(IRenderer* pRenderer) override;

	//Variables
	Rectangle mRectangle{Vector2(-16,-16),Vector2(32,32)};
};

