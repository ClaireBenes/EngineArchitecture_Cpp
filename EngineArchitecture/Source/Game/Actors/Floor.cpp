#include "Floor.h"

#include "Engine/GameTool/Collision/BoxColliderComponent.h"
#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"
#include "Engine/Manager/AssetManager.h"

void Floor::Start()
{
	Actor::Start();
}

void Floor::SetupComponents()
{
	Actor::SetupComponents();

	mTransform->mScale = { 5.0f, 1.0f, 20.0f };

	MeshComponent* meshComponent = new MeshComponent(this, AssetManager::GetMesh("cube"));
	meshComponent->SetTextureIndex(mTextureIndex);
	meshComponent->SetTextureTiling(55, 55);

	BoxColliderComponent* boxComponent = new BoxColliderComponent(this);
}

void Floor::SetTextureIndex(size_t newIndex)
{
	mTextureIndex = newIndex;
}
