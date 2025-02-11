#include "RectangleColliderComponent.h"

#include "../Actor.h"
#include "../../Renderer.h"

void RectangleColliderComponent::Render(Renderer* pRenderer)
{
	//relative transform position
	Rectangle tempRectangle = mRectangle;
	tempRectangle.position += mOwner->mTransform.mPosition;
	pRenderer->DrawRectLine(tempRectangle, mColor);
}

bool RectangleColliderComponent::Collision(Rectangle& otherRectangle)
{
	Rectangle::Collision(mRectangle, otherRectangle);
}
