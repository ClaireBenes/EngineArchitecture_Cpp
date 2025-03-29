#include "Pin.h"

#include "Engine/Manager/AssetManager.h"

#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"
#include "Engine/GameTool/Movement/MoveComponent.h"
#include "Engine/GameTool/Collision/BoxColliderComponent.h"

#include "Engine/Manager/PhysicManager.h"
#include "Engine/GameTool/Utility/Maths.h"

void Pin::Start()
{
	mTransform->mScale = 0.3f;
	mTransform->RotatePitch(180);

	Actor::Start();
}

void Pin::SetupComponents()
{
	MeshComponent* meshComponent = new MeshComponent(this, AssetManager::GetMesh("pin"));
	boxColliderComponent = new BoxColliderComponent(this, Box { { -1.5, -9, -1.5 }, { 1.5, 0, 1.5 } });

	moveComponent = new MoveComponent(this);
	moveComponent->SetCollider(boxColliderComponent);
	moveComponent->mGravityDirection = Vector3::Up * -0.3;
	moveComponent->mFriction = 0.98f;
}

void Pin::Update()
{
	Actor::Update();
}
