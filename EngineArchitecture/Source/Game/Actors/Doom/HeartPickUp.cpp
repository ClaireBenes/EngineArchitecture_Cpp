#include "HeartPickUp.h"

#include "Engine/Manager/AssetManager.h"
#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"
#include "Engine/GameTool/Collision/BoxColliderComponent.h"

#include "Game/Actors/Doom/DoomPlayer.h"

void HeartPickUp::Start()
{
	Actor::Start();
}

void HeartPickUp::SetupComponents()
{
	Actor::SetupComponents();

	MeshComponent* meshComponent = new MeshComponent(this, AssetManager::GetMesh("plane"));
	meshComponent->SetTextureIndex(2);
	//meshComponent->SetTextureTiling(0.2f, 0.2f);

	BoxColliderComponent* boxComponent = new BoxColliderComponent(this);
}

void HeartPickUp::Update()
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
}

void HeartPickUp::OnCollide(Actor* collidedActor)
{
	Actor::OnCollide(collidedActor);

	DoomPlayer* player = dynamic_cast<DoomPlayer*>(collidedActor);
	if (player)
	{
		player->RestoreHealth();
		Destroy();
	}
}

void HeartPickUp::SetPlayer(Actor* player)
{
	mPlayer = player;
}
