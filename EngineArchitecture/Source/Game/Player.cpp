#include "Player.h"

#include "Engine/GameTool/Render/RectangleRenderComponent.h"

void Player::SetupComponents()
{
	RectangleRenderComponent* renderComponent = new RectangleRenderComponent();
	renderComponent->SetOwner(this);
	renderComponent->mColor = { 200,20,20,255 };
	renderComponent->mRectangle.dimensions.x = 70;
}

void Player::Update()
{
	Actor::Update();
}

void Player::Destroy()
{
	Actor::Destroy();
}
