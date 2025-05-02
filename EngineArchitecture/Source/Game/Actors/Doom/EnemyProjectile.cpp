#include "EnemyProjectile.h"

#include "Engine/Manager/AssetManager.h"
#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"
#include "Engine/GameTool/Movement/MoveComponent.h"
#include "Engine/GameTool/Collision/BoxColliderComponent.h"

#include "Game/Actors/Doom/DoomPlayer.h"

void EnemyProjectile::Start()
{
	Actor::Start();

	if (mEnemy != nullptr)
	{
		Vector3 forwardOffset = mEnemy->mTransform->Up() * 5.0f;
		mTransform->mPosition = mEnemy->mTransform->mPosition + forwardOffset;

		mTransform->mPosition.y -= -0.5f;
		mTransform->mPosition.x -= 0.1f;

		mTransform->mRotation = mEnemy->mTransform->mRotation;
	}

	mTransform->mScale = 0.3f;
}

void EnemyProjectile::SetupComponents()
{
	Actor::SetupComponents();

	MeshComponent* meshComponent = new MeshComponent(this, AssetManager::GetMesh("gyroid"));
	meshComponent->SetTextureTiling(0.2f, 0.2f);

	BoxColliderComponent* boxComponent = new BoxColliderComponent(this, { { -0.8f, -0.8f, -0.8f }, { 0.8f, 0.8f, 0.8f } });

	if (mEnemy != nullptr)
	{
		mMoveComponent = new MoveComponent(this);
		mMoveComponent->SetCollider(boxComponent);

		Vector3 speed = mTransform->Up() * 8.0f;
		mMoveComponent->SetSpeed(speed);
	}
}

void EnemyProjectile::Update()
{
	Actor::Update();

	mTransform->mRotation = Quaternion::Concatenate(mTransform->mRotation, Quaternion(mTransform->Up(), Maths::ToRad(8)));
}

void EnemyProjectile::OnCollide(Actor* collidedActor)
{
	Actor::OnCollide(collidedActor);

	DoomPlayer* player = dynamic_cast<DoomPlayer*>(collidedActor);
	if (player)
	{
		player->TakeDamage(1);
	}

	Destroy();
}

void EnemyProjectile::SetEnemy(Actor* enemy)
{
	mEnemy = enemy;
}
