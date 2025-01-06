#include "Player.h"

#include "Engine/GameTool/Render/RectangleRenderComponent.h"

void Player::SetupComponents()
{
	RectangleRenderComponent* renderComponent = new RectangleRenderComponent();
	renderComponent->SetOwner(this);
	renderComponent->mColor = { 255,0,0,255 };
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
