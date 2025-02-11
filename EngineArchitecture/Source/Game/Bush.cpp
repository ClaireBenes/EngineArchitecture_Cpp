#include "Bush.h"

#include "Engine/GameTool/Render/RectangleRenderComponent.h"

void Bush::SetupComponents()
{
	RectangleRenderComponent* renderComponent = new RectangleRenderComponent();
	renderComponent->SetOwner(this);
	renderComponent->mColor = { 20,200,20,255 };
	renderComponent->mRectangle.dimensions.x = 100;
	renderComponent->mRectangle.dimensions.y = 50;
}

void Bush::Update()
{
}

void Bush::Destroy()
{
}
