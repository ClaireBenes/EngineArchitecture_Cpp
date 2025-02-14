#include "Bush.h"

#include "Engine/GameTool/Visual/Render/RectangleRenderComponent.h"
#include "Engine/GameTool/Visual/Render/SpriteRenderComponent.h"
#include "Engine/GameTool/Collision/RectangleColliderComponent.h"
#include "Engine/Manager/AssetManager.h"

void Bush::SetupComponents()
{
	RectangleRenderComponent* renderComponent = new RectangleRenderComponent();
	renderComponent->SetOwner(this);
	renderComponent->mColor = { 20,200,20,255 };
	renderComponent->mRectangle.dimensions.x = 86;
	renderComponent->mRectangle.dimensions.y = 86;

	RectangleColliderComponent* colliderComponent = new RectangleColliderComponent();
	colliderComponent->SetOwner(this);
	colliderComponent->mRectangle.dimensions.x = renderComponent->mRectangle.dimensions.x;
	colliderComponent->mRectangle.dimensions.y = renderComponent->mRectangle.dimensions.y;

	AssetManager::LoadTexture(*mScene->GetRenderer(), "Resources/pokeball.png", "ball");

	SpriteRenderComponent* spriteComponent = new SpriteRenderComponent(AssetManager::GetTexture("ball"));
	spriteComponent->SetOwner(this);
	spriteComponent->AddSprite();


	//spriteComponent->mColor = { 255, 255, 255, 255 };
	spriteComponent->mRectangle.dimensions.x = 86;
	spriteComponent->mRectangle.dimensions.y = 86;

}

void Bush::Update()
{
}

void Bush::Destroy()
{
}
