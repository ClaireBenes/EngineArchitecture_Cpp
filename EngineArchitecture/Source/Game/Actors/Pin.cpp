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
}

void Pin::Update()
{
	Actor::Update();

	//ColliderComponent* collidedComponent = moveComponent->CheckCollision();

	//if (collidedComponent != nullptr && collidedComponent->GetOwner()->GetComponentOfType<MoveComponent>() != nullptr)
	//{
	//	PhysicManager& physicManager = PhysicManager::Instance();
	//	Vector3 collisionNormal = physicManager.GetCollisionNormal(boxColliderComponent, collidedComponent);
	//	Vector3 otherVelocity = collidedComponent->GetOwner()->GetComponentOfType<MoveComponent>()->mVelocity;
	//	float impactStrength = Vector3::Dot(otherVelocity, collisionNormal);

	//	// Ensure some movement
	//	if (impactStrength > 0.1f)
	//	{
	//		moveComponent->mVelocity += collisionNormal * impactStrength;
	//	}

	//	moveComponent->mVelocity += collisionNormal * impactStrength;
	//	moveComponent->SetSpeed(0.1f);
	//	//moveComponent->mVelocity *= 0.8f;
	//}

	// Apply friction (damping)
	float dampingFactor = 0.98f;
	moveComponent->mVelocity *= dampingFactor;

	if (moveComponent->mVelocity.MagnitudeSqr() < 0.0001f)
	{
		moveComponent->mVelocity = Vector3(0, 0, 0);
	}

	mTransform->mPosition = mTransform->mPosition + moveComponent->mVelocity * Time::deltaTime;
}
