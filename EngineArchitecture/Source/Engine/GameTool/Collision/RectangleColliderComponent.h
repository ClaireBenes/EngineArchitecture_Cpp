#pragma once

#include "ColliderComponent.h"
#include "../Rectangle.h"

//Rectangle
class RectangleColliderComponent : public ColliderComponent
{
public:
	//Variables
	void Render(Renderer* pRenderer) override;
	bool Collision();
	Rectangle mRectangle{ Vector2(-16,-16),Vector2(32,32) };
};

