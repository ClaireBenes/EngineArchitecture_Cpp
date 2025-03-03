#include "RectangleRenderComponent.h"

#include "Engine/GameTool/Actor.h"
#include "Engine/Renderer/IRenderer.h"

void RectangleRenderComponent::Render(IRenderer* pRenderer)
{
	//relative transform position
	Rectangle tempRectangle = mRectangle;
	tempRectangle.position += mOwner->mTransform.mPosition;
	pRenderer->DrawRect(tempRectangle, mColor);
}
