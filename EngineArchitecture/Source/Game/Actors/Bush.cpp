#include "Bush.h"

#include "Engine/GameTool/Visual/Render/RectangleRenderComponent.h"
#include "Engine/GameTool/Visual/Render/Sprite/SpriteRenderComponent.h"
#include "Engine/GameTool/Collision/RectangleColliderComponent.h"
#include "Engine/Manager/AssetManager.h"

void Bush::SetupComponents()
{
	AssetManager::LoadTexture(*mScene->GetRenderer(), "Resources/Ground.png", "ground");

	SpriteRenderComponent* spriteComponent = new SpriteRenderComponent(this, AssetManager::GetTexture("ground"));
	spriteComponent->SetNewDimensions(186, 31);

	colliderComponent = new RectangleColliderComponent();
	colliderComponent->SetOwner(this);
	colliderComponent->mRectangle.dimensions.x = spriteComponent->mRectangle.dimensions.x;
	colliderComponent->mRectangle.dimensions.y = spriteComponent->mRectangle.dimensions.y;
}

void Bush::Update()
{
	//printf("Bush : {%f , %f}, {%f , %f}\n", colliderComponent->GetWorldRectangle().position.x, 
	//	colliderComponent->GetWorldRectangle().position.x + colliderComponent->GetWorldRectangle().dimensions.x,
	//	colliderComponent->GetWorldRectangle().position.y,
	//	colliderComponent->GetWorldRectangle().position.y + colliderComponent->GetWorldRectangle().dimensions.y);
}

void Bush::Destroy()
{
}
