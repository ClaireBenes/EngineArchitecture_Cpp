#include "AmmoPickUp.h"

#include "Engine/Manager/AssetManager.h"
#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"
#include "Engine/GameTool/Collision/BoxColliderComponent.h"

#include "Game/Actors/Doom/DoomPlayer.h"

void AmmoPickUp::Start()
{
	Actor::Start();
}

void AmmoPickUp::SetupComponents()
{
	Actor::SetupComponents();

	MeshComponent* meshComponent = new MeshComponent(this, AssetManager::GetMesh("plane"));
	meshComponent->SetTextureIndex(3);
	//meshComponent->SetTextureTiling(0.2f, 0.2f);

	BoxColliderComponent* boxComponent = new BoxColliderComponent(this);
}

void AmmoPickUp::Update()
{
	Actor::Update();

	if(mPlayer != nullptr)
	{
		Vector3 playerPos = mTransform->mPosition - mPlayer->mTransform->mPosition;
		playerPos.y = 0.0f;
		playerPos = playerPos.Normalized();

		mTransform->LookAt(playerPos);
		mTransform->RotatePitch(-90);
	}
}

void AmmoPickUp::OnCollide(Actor* collidedActor)
{
	Actor::OnCollide(collidedActor);

	DoomPlayer* player = dynamic_cast< DoomPlayer* >( collidedActor );
	if(player)
	{
		player->RestoreAmmo();
		Destroy();
	}
}

void AmmoPickUp::SetPlayer(Actor* player)
{
	mPlayer = player;
}
