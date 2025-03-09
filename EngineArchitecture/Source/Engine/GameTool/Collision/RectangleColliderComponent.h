#pragma once

#include "ColliderComponent.h"
#include "../Rectangle.h"

//Rectangle
class RectangleColliderComponent : public ColliderComponent
{
public:
	RectangleColliderComponent(Actor* pOwner);

	//Variables
	void DebugRender(IRenderer* pRenderer) override;

	Rectangle GetWorldRectangle() const;

	//AABB Collision Check
	bool Collision(const Rectangle& otherRectangle);
	bool Collision(const ColliderComponent* pComponent) override;

	Rectangle mRectangle{ Vector2(-16,-16),Vector2(32,32) };
};

