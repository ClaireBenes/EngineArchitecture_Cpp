#include "Projectile.h"

#include "Engine/Manager/AssetManager.h"
#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"
#include "Engine/GameTool/Movement/MoveComponent.h"
#include "Engine/GameTool/Collision/BoxColliderComponent.h"

void Projectile::Start()
{
	Actor::Start();
}

void Projectile::SetupComponents()
{
	Actor::SetupComponents();

	MeshComponent* meshComponent = new MeshComponent(this, AssetManager::GetMesh("caillou"));
	BoxColliderComponent* boxComponent = new BoxColliderComponent(this);

	moveComponent = new MoveComponent(this);
	moveComponent->SetCollider(boxComponent);
	moveComponent->SetSpeed(Vector3(0, 0, 20));
	moveComponent->AddForce(Vector3(0, 0, 0.5f));
}

void Projectile::Update()
{
	Actor::Update();
}
