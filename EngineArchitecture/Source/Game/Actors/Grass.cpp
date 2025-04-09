#include "Grass.h"

#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"
#include "Engine/Manager/AssetManager.h"

void Grass::Start()
{
	Actor::Start();
}

void Grass::SetupComponents()
{
	mTransform->mScale = { 0.5f, 0.5f, 0.5f };

	MeshComponent* meshComponent = new MeshComponent(this, AssetManager::GetMesh("grassBlade"));
	//meshComponent->SetTextureTiling(15, 15);

	//BoxColliderComponent* boxComponent = new BoxColliderComponent(this);
}
