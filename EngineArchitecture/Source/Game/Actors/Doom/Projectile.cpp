#include "Projectile.h"

#include "Engine/Manager/AssetManager.h"
#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"
#include "Engine/GameTool/Movement/MoveComponent.h"
#include "Engine/GameTool/Collision/BoxColliderComponent.h"


void Projectile::Start()
{
	Actor::Start();

	if (mPlayer != nullptr)
	{
		Vector3 forwardOffset = mPlayer->mTransform->Forward() * 2.0f;
		mTransform->mPosition = mPlayer->mTransform->mPosition + forwardOffset;

		mTransform->mPosition.y -= 0.2f;
		mTransform->mPosition.x -= 0.1f;
	}

	mTransform->mScale = 0.8f;
}

void Projectile::SetupComponents()
{
	Actor::SetupComponents();

	MeshComponent* meshComponent = new MeshComponent(this, AssetManager::GetMesh("caillou"));
	meshComponent->SetTextureTiling(0.1f, 0.1f);

	BoxColliderComponent* boxComponent = new BoxColliderComponent(this, { { -0.3f, -0.3f, -0.3f }, { 0.3f, 0.3f, 0.3f } });

	if (mPlayer != nullptr)
	{
		moveComponent = new MoveComponent(this);
		moveComponent->SetCollider(boxComponent);

		Vector3 speed = mPlayer->mTransform->Forward() * 20.0f;
		Vector3 force = mPlayer->mTransform->Forward() * 0.5f;
		moveComponent->SetSpeed(speed);
		moveComponent->AddForce(force);
	}

}

void Projectile::Update()
{
	Actor::Update();
}

void Projectile::OnCollide(Actor* collidedActor)
{
	Actor::OnCollide(collidedActor);

	Destroy();
}

void Projectile::SetPlayer(Actor* player)
{
	mPlayer = player;
}
