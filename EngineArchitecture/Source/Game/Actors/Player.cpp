#include "Player.h"

#include "Engine/GameTool/Visual/Render/RectangleRenderComponent.h"
#include "Engine/GameTool/Collision/RectangleColliderComponent.h"
#include "Engine/GameTool/Visual/Render/Sprite/SpriteRenderComponent.h"
#include "Engine/Manager/PhysicManager.h"
#include "Engine/Manager/AssetManager.h"

void Player::SetupComponents()
{
	RectangleRenderComponent* renderComponent = new RectangleRenderComponent();
	renderComponent->SetOwner(this);
	renderComponent->mColor = { 20,20,200,255 };

	colliderComponent = new RectangleColliderComponent();
	colliderComponent->SetOwner(this);
	colliderComponent->mRectangle.dimensions.x = renderComponent->mRectangle.dimensions.x;
	colliderComponent->mRectangle.dimensions.y = renderComponent->mRectangle.dimensions.y;
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

	PhysicManager& physicManager = PhysicManager::Instance();

	if(physicManager.Collision(colliderComponent))
	{
		printf("dfgfdsgfdgdfgD");
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
