#include "RectangleRenderComponent.h"

#include "Engine/GameTool/Actor.h"
#include "Engine/Renderer.h"

void RectangleRenderComponent::Render(Renderer* pRenderer)
{
	//relative transform position
	Rectangle tempRectangle = mRectangle;
	tempRectangle.position += mOwner->mTransform.mPosition;
	pRenderer->DrawRect(tempRectangle, mColor);
}
