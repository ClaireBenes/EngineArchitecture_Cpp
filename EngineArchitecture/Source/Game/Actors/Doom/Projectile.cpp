#include "Projectile.h"

#include "Engine/Manager/AssetManager.h"
#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"
#include "Engine/GameTool/Movement/MoveComponent.h"
#include "Engine/GameTool/Collision/BoxColliderComponent.h"

#include "Game/Actors/TheDescent/SimpleEnemy.h"


void Projectile::Start()
{
	Actor::Start();

	if (mPlayer != nullptr)
	{
		Vector3 forwardOffset = mPlayer->mTransform->Forward() * 5.0f;
		mTransform->mPosition = mPlayer->mTransform->mPosition + forwardOffset;

		mTransform->mPosition.y -= 0.5f;
	}

	mTransform->mScale = 1.6f;
}

void Projectile::SetupComponents()
{
	Actor::SetupComponents();

	MeshComponent* meshComponent = new MeshComponent(this, AssetManager::GetMesh("caillou"));
	meshComponent->SetTextureTiling(0.5f, 0.5f);

	BoxColliderComponent* boxComponent = new BoxColliderComponent(this, { { -0.5f, -0.5f, -1.5f }, { 1.5f, 2.5f, 1.5f } });

	if (mPlayer != nullptr)
	{
		mMoveComponent = new MoveComponent(this);
		mMoveComponent->SetCollider(boxComponent);

		Vector3 speed = mPlayer->mTransform->Forward() * 100.0f;
		Vector3 force = mPlayer->mTransform->Forward() * 0.5f;
		mMoveComponent->SetSpeed(speed);
		mMoveComponent->AddForce(force);
	}
}

void Projectile::Update()
{
	Actor::Update();
}

void Projectile::OnCollide(Actor* collidedActor)
{
	Actor::OnCollide(collidedActor);

	SimpleEnemy* enemy = dynamic_cast<SimpleEnemy*>(collidedActor);
	if (enemy)
	{
		enemy->TakeDamage(1.0f);
	}

	Destroy();
}

void Projectile::SetPlayer(Actor* player)
{
	mPlayer = player;
}
