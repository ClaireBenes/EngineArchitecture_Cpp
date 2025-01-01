#include "RectangleRenderComponent.h"

#include "Renderer.h"
#include "Actor.h"

void RectangleRenderComponent::Render(Renderer* pRenderer)
{
	Rectangle tempRectangle = mRectangle;
	tempRectangle.position += mOwner->mTransform.mPosition;
	pRenderer->DrawRect(tempRectangle, mColor);
}
