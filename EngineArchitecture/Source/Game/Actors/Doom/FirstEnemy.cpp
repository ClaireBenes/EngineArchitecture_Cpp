#include "FirstEnemy.h"

#include "Engine/Manager/AssetManager.h"
#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"
#include "Engine/GameTool/Collision/BoxColliderComponent.h"
#include "Engine/GameTool/Movement/MoveComponent.h"

void FirstEnemy::Start()
{
	mTransform->mScale = { 1.0f, 1.0f, 1.8f };
	mTransform->RotatePitch(90);

	Actor::Start();
}

void FirstEnemy::SetupComponents()
{
	MeshComponent* meshComponent = new MeshComponent(this, AssetManager::GetMesh("plane"));
	BoxColliderComponent* boxComponent = new BoxColliderComponent(this, {{ -1, -1.8, 0 }, { 1, 1.8, 0 }});

	moveComponent = new MoveComponent(this);
	moveComponent->SetCollider(boxComponent);
	moveComponent->mGravityDirection = Vector3::Up * -0.3;
	//moveComponent->mFriction = 0.98f;
}

void FirstEnemy::Update()
{
	Actor::Update();

	if (mPlayer != nullptr)
	{
		Vector3 playerPos = mPlayer->mTransform->mPosition - mTransform->mPosition;
		playerPos.y = 0.0f;
		playerPos = playerPos.Normalized();

		mTransform->LookAt(playerPos);

		float yaw = -Maths::ATan2(playerPos.x, playerPos.z);
		mTransform->mRotation = Quaternion(0.0f, yaw, 0.0f);
		mTransform->RotatePitch(90);

		//mTransform->RotateYaw(Maths::ToDeg(yaw));
	}
}

void FirstEnemy::SetPlayer(DoomPlayer* pNewPlayer)
{
	mPlayer = pNewPlayer;
}
