#include "Grass.h"

#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"
#include "Engine/Manager/AssetManager.h"

void Grass::Start()
{
	Actor::Start();
}

void Grass::SetupComponents()
{
	Actor::SetupComponents();

	mTransform->mScale = { 5.5f, 2.5f, 5.5f };

	MeshComponent* meshComponent = new MeshComponent(this, AssetManager::GetMesh("grassBlade"));
	meshComponent->SetTextureTiling(0.1, 0.001);

	//BoxColliderComponent* boxComponent = new BoxColliderComponent(this);
}
