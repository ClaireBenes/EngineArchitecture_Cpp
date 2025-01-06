#include "RectangleRenderComponent.h"

#include "../Actor.h"
#include "../../Renderer.h"

void RectangleRenderComponent::Render(Renderer* pRenderer)
{
	//relative transform position
	Rectangle tempRectangle = mRectangle;
	tempRectangle.position += mOwner->mTransform.mPosition;
	pRenderer->DrawRect(tempRectangle, mColor);
}
