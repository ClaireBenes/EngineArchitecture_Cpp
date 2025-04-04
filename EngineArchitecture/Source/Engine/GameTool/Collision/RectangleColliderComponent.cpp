#include "RectangleColliderComponent.h"

#include "../Actor.h"
#include "Engine/Renderer/IRenderer.h"

RectangleColliderComponent::RectangleColliderComponent(Actor* pOwner):
ColliderComponent(pOwner)
{
}

void RectangleColliderComponent::DebugRender(IRenderer* pRenderer)
{
	pRenderer->DrawRectLine(GetWorldRectangle(), mColor);
}

Rectangle RectangleColliderComponent::GetWorldRectangle() const
{
	Rectangle tempRectangle = mRectangle;
	tempRectangle.position.x += mOwner->mTransform->mPosition.x;
	tempRectangle.position.y += mOwner->mTransform->mPosition.y;

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
