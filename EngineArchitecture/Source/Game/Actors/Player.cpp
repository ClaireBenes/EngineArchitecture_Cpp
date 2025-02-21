#include "Player.h"

#include "Engine/GameTool/Visual/Render/Sprite/AnimatedSpriteRenderComponent.h"
#include "Engine/GameTool/Collision/RectangleColliderComponent.h"
#include "Engine/GameTool/Movement/Controller/PlayerController.h"

#include "Engine/GameTool/Movement/Controller/PlatformerPlayerController.h"

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
	colliderComponent->mRectangle.dimensions.x = animatedSpriteComponent->mRectangle.dimensions.x / 2;
	colliderComponent->mRectangle.dimensions.y = animatedSpriteComponent->mRectangle.dimensions.y / 1.3f;
	colliderComponent->mRectangle.position.x = animatedSpriteComponent->mRectangle.position.x + (animatedSpriteComponent->mRectangle.dimensions.x / 4);
	colliderComponent->mRectangle.position.y = animatedSpriteComponent->mRectangle.position.y + (animatedSpriteComponent->mRectangle.dimensions.y / 8);

	PlatformerPlayerController* platformPlayercontroller = new PlatformerPlayerController(this);
	platformPlayercontroller->SetCollider(colliderComponent);
}

void Player::Update()
{
	Actor::Update();
}

void Player::Destroy()
{
	Actor::Destroy();
}
