#include "Player.h"

#include "Engine/GameTool/Visual/Render/RectangleRenderComponent.h"
#include "Engine/GameTool/Collision/RectangleColliderComponent.h"
#include "Engine/GameTool/Visual/Render/Sprite/AnimatedSpriteRenderComponent.h"
#include "Engine/Manager/PhysicManager.h"
#include "Engine/Manager/AssetManager.h"

#include <vector>

void Player::SetupComponents()
{
	AssetManager::LoadTexturesFromFolder(*mScene->GetRenderer(), "Resources/Characters/Walk", allTextures);

	animatedSpriteComponent = new AnimatedSpriteRenderComponent(allTextures);
	animatedSpriteComponent->SetOwner(this);
	animatedSpriteComponent->AddSprite();
	animatedSpriteComponent->SetAnimationFps(10.0f);

	animatedSpriteComponent->SetNewDimensions(86, 86);

	colliderComponent = new RectangleColliderComponent();
	colliderComponent->SetOwner(this);
	colliderComponent->mRectangle.dimensions.x = animatedSpriteComponent->mRectangle.dimensions.x;
	colliderComponent->mRectangle.dimensions.y = animatedSpriteComponent->mRectangle.dimensions.y;
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
		animatedSpriteComponent->mFlip = Renderer::Flip::None;
	}
	if(mIsMovingLeft)
	{
		mTransform.mPosition.x -= mSpeedX * Time::deltaTime;
		animatedSpriteComponent->mFlip = Renderer::Flip::Horizontal;
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
