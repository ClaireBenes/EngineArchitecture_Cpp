#include "WinBox.h"

#include "Engine/Manager/AssetManager.h"
#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"
#include "Engine/GameTool/Collision/BoxColliderComponent.h"

#include "Game/Actors/Doom/DoomPlayer.h"

void WinBox::Start()
{
	Actor::Start();

	mTransform->mScale = { 0.5, 0.5, 0.5 };
	mTransform->RotateYaw(20);
}

void WinBox::SetupComponents()
{
	Actor::SetupComponents();

	MeshComponent* meshComponent = new MeshComponent(this, AssetManager::GetMesh("bellBag"));
	BoxColliderComponent* boxComponent = new BoxColliderComponent(this, Box { { -2, -2, -2 }, { 2, 2, 2 } } );
}

void WinBox::Update()
{
	Actor::Update();
}

void WinBox::OnCollide(Actor* collidedActor)
{
	Actor::OnCollide(collidedActor);

	DoomPlayer* player = dynamic_cast<DoomPlayer*>(collidedActor);
	if (player)
	{
		player->EndGame(true);
	}
}

void WinBox::SetPlayer(Actor* player)
{
	mPlayer = player;
}
