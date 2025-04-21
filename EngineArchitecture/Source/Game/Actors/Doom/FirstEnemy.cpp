#include "FirstEnemy.h"

#include "Engine/Manager/AssetManager.h"
#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"
#include "Engine/GameTool/Collision/BoxColliderComponent.h"
#include "Engine/GameTool/Movement/MoveComponent.h"

#include "Game/Actors/Doom/Projectile.h"

void FirstEnemy::Start()
{
	mTransform->mScale = { 1.0f, 1.0f, 1.8f };
	mTransform->RotatePitch(90);

	Actor::Start();
}

void FirstEnemy::SetupComponents()
{
	Actor::SetupComponents();

	mMeshComponent = new MeshComponent(this, AssetManager::GetMesh("plane"));
	mMeshComponent->SetTextureIndex(mTextureIndex);
	boxComponent = new BoxColliderComponent(this, {{ -1, -1.8, -0.5 }, { 1, 1.8, 0.5 }});

	moveComponent = new MoveComponent(this);
	moveComponent->SetCollider(boxComponent);
	moveComponent->mGravityDirection = -Vector3::Up * 0.3;
	moveComponent->mFriction = 7.0f;
}

void FirstEnemy::Update()
{
	Actor::Update();

	if (mPlayer != nullptr)
	{
		Vector3 playerPos = mTransform->mPosition - mPlayer->mTransform->mPosition;
		playerPos.y = 0.0f;
		playerPos = playerPos.Normalized();

		mTransform->LookAt(playerPos);
		mTransform->RotatePitch(-90);
	}

	//Damage
	if (mIsTakingDamage)
	{
		mCurrentDamageDelay -= Time::deltaTime;

		if (mCurrentDamageDelay <= 0.0f)
		{
			mMeshComponent->SetTextureIndex(0);
			mCurrentDamageDelay = mDamageDelay;
			mIsTakingDamage = false;

			if (mHealth <= 0)
			{
				Destroy();
			}
		}
	}
}

void FirstEnemy::SetPlayer(DoomPlayer* pNewPlayer)
{
	mPlayer = pNewPlayer;
}

void FirstEnemy::SetTextureIndex(size_t newIndex)
{
	mTextureIndex = newIndex;
}

void FirstEnemy::TakeDamage(float damage)
{
	if (mMeshComponent != nullptr)
	{
		mMeshComponent->SetTextureIndex(1);
		mIsTakingDamage = true;
	}

	mHealth -= damage;
}
