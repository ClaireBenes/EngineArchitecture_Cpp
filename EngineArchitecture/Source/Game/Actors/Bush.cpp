#include "Bush.h"

#include "Engine/GameTool/Visual/Render/RectangleRenderComponent.h"
#include "Engine/GameTool/Visual/Render/Sprite/SpriteRenderComponent.h"
#include "Engine/GameTool/Collision/RectangleColliderComponent.h"
#include "Engine/Manager/AssetManager.h"

void Bush::SetupComponents()
{
	AssetManager::LoadTexture(*mScene->GetRenderer(), "Resources/pokeball.png", "ball");

	RectangleRenderComponent* rectangleComponent = new RectangleRenderComponent();
	rectangleComponent->SetOwner(this);
	rectangleComponent->mColor = { 60,230,60,255 };
	rectangleComponent->mRectangle.dimensions.x = 512;
	rectangleComponent->mRectangle.dimensions.y = 86;

	RectangleColliderComponent* colliderComponent = new RectangleColliderComponent();
	colliderComponent->SetOwner(this);
	colliderComponent->mRectangle.dimensions.x = rectangleComponent->mRectangle.dimensions.x;
	colliderComponent->mRectangle.dimensions.y = rectangleComponent->mRectangle.dimensions.y;
}

void Bush::Update()
{
}

void Bush::Destroy()
{
}
