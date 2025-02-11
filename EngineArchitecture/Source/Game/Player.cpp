#include "Player.h"

#include "Engine/GameTool/Render/RectangleRenderComponent.h"

void Player::SetupComponents()
{
	RectangleRenderComponent* renderComponent = new RectangleRenderComponent();
	renderComponent->SetOwner(this);
	renderComponent->mColor = { 200,20,20,255 };
}

void Player::Update()
{
	Actor::Update();

	//player paddle movement
	if(mIsMovingUp)
	{
		mTransform.mPosition.y -= mSpeedY * Time::deltaTime;
	}
	if(mIsMovingDown)
	{
		mTransform.mPosition.y += mSpeedY * Time::deltaTime;
	}
	if(mIsMovingRight)
	{
		mTransform.mPosition.x += mSpeedX * Time::deltaTime;
	}
	if(mIsMovingLeft)
	{
		mTransform.mPosition.x -= mSpeedX * Time::deltaTime;
	}
}

void Player::Destroy()
{
	Actor::Destroy();
}

void Player::StopMoving()
{
	mIsMovingUp = false;
	mIsMovingDown = false;
	mIsMovingRight = false;
	mIsMovingLeft = false;
}
