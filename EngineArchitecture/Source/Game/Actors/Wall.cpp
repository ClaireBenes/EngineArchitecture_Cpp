#include "Wall.h"

#include "Engine/GameTool/Visual/Render/Sprite/SpriteRenderComponent.h"
#include "Engine/Manager/AssetManager.h"
#include "Engine/GameTool/Utility/Maths.h"

void Wall::SetupComponents()
{
	AssetManager::LoadTexture(*mScene->GetRenderer(), "Resources/wall.jpg", "wall");

	SpriteRenderComponent* spriteComponent = new SpriteRenderComponent(this, AssetManager::GetTexture("wall"));
	mTransform->mScale = 0.5f;
	mTransform->RotateRoll(90);
}

void Wall::Update()
{
}

void Wall::Destroy()
{
}
