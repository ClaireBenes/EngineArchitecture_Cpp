#include "SimpleEnemy.h"

#include "Engine/Manager/AssetManager.h"
#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"
#include "Engine/GameTool/Collision/BoxColliderComponent.h"
#include "Engine/GameTool/Movement/MoveComponent.h"

void SimpleEnemy::Start()
{
	mTransform->mScale = { 0.007f, 0.007f, 0.007f };

	Actor::Start();
}

void SimpleEnemy::SetupComponents()
{
	Actor::SetupComponents();

	mMeshComponent = new MeshComponent(this, AssetManager::GetMesh("jellfish"));
	mMeshComponent->SetTextureIndex(mTextureIndex);
	mBoxComponent = new BoxColliderComponent(this, {{ -1000, -6000.8, -1000.5 }, { 1000, 6000.8, 1000.5 }});
}

void SimpleEnemy::Update()
{
	Actor::Update();

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

void SimpleEnemy::SetTextureIndex(size_t newIndex)
{
	mTextureIndex = newIndex;
}

void SimpleEnemy::TakeDamage(float damage)
{
	if (mMeshComponent != nullptr)
	{
		mMeshComponent->SetTextureIndex(1);
		mIsTakingDamage = true;
	}

	mHealth -= damage;
}
