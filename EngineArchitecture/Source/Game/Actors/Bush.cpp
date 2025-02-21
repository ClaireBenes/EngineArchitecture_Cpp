#include "Bush.h"

#include "Engine/GameTool/Visual/Render/RectangleRenderComponent.h"
#include "Engine/GameTool/Visual/Render/Sprite/SpriteRenderComponent.h"
#include "Engine/GameTool/Collision/RectangleColliderComponent.h"
#include "Engine/Manager/AssetManager.h"

void Bush::SetupComponents()
{
	AssetManager::LoadTexture(*mScene->GetRenderer(), "Resources/pokeball.png", "ball");

	SpriteRenderComponent* spriteComponent = new SpriteRenderComponent(this, AssetManager::GetTexture("ball"));
	spriteComponent->SetNewDimensions(512, 86);

	RectangleColliderComponent* colliderComponent = new RectangleColliderComponent();
	colliderComponent->SetOwner(this);
	colliderComponent->mRectangle.dimensions.x = spriteComponent->mRectangle.dimensions.x;
	colliderComponent->mRectangle.dimensions.y = spriteComponent->mRectangle.dimensions.y;
}

void Bush::Update()
{
}

void Bush::Destroy()
{
}
