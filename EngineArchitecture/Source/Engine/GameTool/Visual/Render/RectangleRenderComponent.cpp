#include "RectangleRenderComponent.h"

#include "Engine/GameTool/Actor.h"
#include "Engine/Renderer/IRenderer.h"

void RectangleRenderComponent::Render(IRenderer* pRenderer)
{
	//relative transform position
	Rectangle tempRectangle = mRectangle;
	tempRectangle.position.x += mOwner->mTransform->mPosition.x;
	tempRectangle.position.y += mOwner->mTransform->mPosition.y;

	pRenderer->DrawRect(tempRectangle, mColor);
}
