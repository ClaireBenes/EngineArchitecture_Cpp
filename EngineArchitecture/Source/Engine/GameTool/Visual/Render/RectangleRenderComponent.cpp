#include "RectangleRenderComponent.h"

#include "Engine/GameTool/Actor.h"
#include "Engine/Renderer/RendererSDL.h"

void RectangleRenderComponent::Render(RendererSDL* pRenderer)
{
	//relative transform position
	Rectangle tempRectangle = mRectangle;
	tempRectangle.position += mOwner->mTransform.mPosition;
	pRenderer->DrawRect(tempRectangle, mColor);
}
