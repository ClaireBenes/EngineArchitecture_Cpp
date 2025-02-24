#include "RectangleColliderComponent.h"

#include "../Actor.h"
#include "../../Renderer.h"

void RectangleColliderComponent::DebugRender(Renderer* pRenderer)
{
	pRenderer->DrawRectLine(GetWorldRectangle(), mColor);
}

Rectangle RectangleColliderComponent::GetWorldRectangle() const
{
	Rectangle tempRectangle = mRectangle;
	tempRectangle.position += mOwner->mTransform.mPosition;
	return tempRectangle;
}

bool RectangleColliderComponent::Collision(const Rectangle& otherRectangle)
{
	return Rectangle::Collision(GetWorldRectangle(), otherRectangle);
}

bool RectangleColliderComponent::Collision(const ColliderComponent* pComponent)
{
	if( const RectangleColliderComponent* pRectangleComponent = dynamic_cast<const RectangleColliderComponent*>(pComponent))
	{
		return Collision(pRectangleComponent->GetWorldRectangle());
	}
	return false;
}
