#include "Floor.h"
#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"
#include "Engine/GameTool/Visual/Mesh/Mesh.h"

#include "Engine/GameTool/Collision/BoxColliderComponent.h"
#include "Engine/Renderer/RendererGL.h"
#include "Engine/Manager/AssetManager.h"

void Floor::Start()
{
	Actor::Start();
}

void Floor::SetupComponents()
{
	mTransform->mScale = { 5.0f, 1.0f, 20.0f };

	MeshComponent* meshComponent = new MeshComponent(this, AssetManager::GetMesh("cube"));
	meshComponent->SetTextureIndex(mTextureIndex);
	BoxColliderComponent* boxComponent = new BoxColliderComponent(this);
}

void Floor::SetTextureIndex(size_t newIndex)
{
	mTextureIndex = newIndex;
}
