#include "Wall.h"

#include "Engine/GameTool/Visual/Render/Sprite/SpriteRenderComponent.h"
#include "Engine/Manager/AssetManager.h"

void Wall::SetupComponents()
{
	AssetManager::LoadTexture(*mScene->GetRenderer(), "Resources/wall.jpg", "wall");

	SpriteRenderComponent* spriteComponent = new SpriteRenderComponent(this, AssetManager::GetTexture("wall"));
}

void Wall::Update()
{
}

void Wall::Destroy()
{
}
