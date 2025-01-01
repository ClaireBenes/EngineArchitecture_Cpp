#include "Player.h"

#include "Engine/RectangleRenderComponent.h"

void Player::SetupComponents()
{
	RectangleRenderComponent* renderComponent = new RectangleRenderComponent();
	renderComponent->SetOwner(this);
	renderComponent->mColor = { 255,0,0,255 };
}

void Player::Update()
{
	Actor::Update();
}

void Player::Destroy()
{
	Actor::Destroy();
}
