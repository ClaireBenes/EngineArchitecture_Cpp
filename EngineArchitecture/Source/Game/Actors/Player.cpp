#include "Player.h"

#include "Engine/GameTool/Visual/Render/RectangleRenderComponent.h"
#include "Engine/GameTool/Visual/Render/Sprite/AnimatedSpriteRenderComponent.h"

#include "Engine/GameTool/Collision/RectangleColliderComponent.h"

#include "Engine/GameTool/Movement/Controller/PlayerController.h"

#include "Engine/Manager/PhysicManager.h"
#include "Engine/Manager/AssetManager.h"

#include <vector>

void Player::SetupComponents()
{
	AssetManager::LoadTexturesFromFolder(*mScene->GetRenderer(), "Resources/Characters/Walk", allTextures);

	animatedSpriteComponent = new AnimatedSpriteRenderComponent(this, allTextures);
	animatedSpriteComponent->SetAnimationFps(10.0f);
	animatedSpriteComponent->SetNewDimensions(86, 86);

	colliderComponent = new RectangleColliderComponent();
	colliderComponent->SetOwner(this);
	colliderComponent->mRectangle.dimensions.x = animatedSpriteComponent->mRectangle.dimensions.x;
	colliderComponent->mRectangle.dimensions.y = animatedSpriteComponent->mRectangle.dimensions.y;

	playerController = new PlayerController(this);
}

void Player::Update()
{
	Actor::Update();

	playerController->Update();

	PhysicManager& physicManager = PhysicManager::Instance();

	if(physicManager.Collision(colliderComponent))
	{
		printf("IN COLLISION | ");
	}
}

void Player::Destroy()
{
	Actor::Destroy();
}
