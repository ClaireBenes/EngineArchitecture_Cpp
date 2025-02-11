#include "Bush.h"

#include "Engine/GameTool/Render/RectangleRenderComponent.h"
#include "Engine/GameTool/Collision/RectangleColliderComponent.h"

void Bush::SetupComponents()
{
	RectangleRenderComponent* renderComponent = new RectangleRenderComponent();
	renderComponent->SetOwner(this);
	renderComponent->mColor = { 20,200,20,255 };
	renderComponent->mRectangle.dimensions.x = 100;
	renderComponent->mRectangle.dimensions.y = 50;

	RectangleColliderComponent* colliderComponent = new RectangleColliderComponent();
	colliderComponent->SetOwner(this);
	colliderComponent->mRectangle.dimensions.x = renderComponent->mRectangle.dimensions.x;
	colliderComponent->mRectangle.dimensions.y = renderComponent->mRectangle.dimensions.y;
}

void Bush::Update()
{
}

void Bush::Destroy()
{
}
