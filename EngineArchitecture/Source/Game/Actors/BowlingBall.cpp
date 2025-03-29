#include "BowlingBall.h"

#include "Engine/Manager/AssetManager.h"

#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"
#include "Engine/GameTool/Movement/MoveComponent.h"
#include "Engine/GameTool/Collision/BoxColliderComponent.h"

void BowlingBall::Start()
{
	//mTransform->mScale = 0.3f;
	Actor::Start();
}

void BowlingBall::SetupComponents()
{
	MeshComponent* meshComponent = new MeshComponent(this, AssetManager::GetMesh("ball"));
	BoxColliderComponent* boxComponent = new BoxColliderComponent(this);

	MoveComponent* moveComponent = new MoveComponent(this);
	moveComponent->SetCollider(boxComponent);
	moveComponent->mGravityDirection = Vector3::Up * -2;
	moveComponent->SetSpeed(Vector3(0, 0, 15));
	moveComponent->AddForce(Vector3(0, 0, 0.1f));
}

void BowlingBall::Update()
{
	Actor::Update();
}
