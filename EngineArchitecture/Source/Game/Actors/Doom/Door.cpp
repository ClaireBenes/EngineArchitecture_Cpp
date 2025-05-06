#include "Door.h"

#include "Engine/Manager/AssetManager.h"
#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"
#include "Engine/GameTool/Collision/BoxColliderComponent.h"

#include "Game/Actors/Doom/DoomPlayer.h"

void Door::Start()
{
	Actor::Start();

	mTransform->RotateYaw(180);
	mTransform->mScale = Vector3(1.3f, 2, 0.5f);
}

void Door::SetupComponents()
{
	Actor::SetupComponents();

	MeshComponent* meshComponent = new MeshComponent(this, AssetManager::GetMesh("door"));

	float yBox = mTransform->mScale.y;
	mBoxComponent = new BoxColliderComponent(this, Box { { 0, -yBox, -1.0 }, { 2, yBox, 1.0 } });
}

void Door::Update()
{
	Actor::Update();

	if (mIsturning && !mAlreadyTurned)
	{
		float delta = -2.0f;
		mCurrentYaw += delta;

		if (mCurrentYaw <= -90.0f)
		{
			delta -= (mCurrentYaw + 90.0f);

			float yBox = mTransform->mScale.y;
			mBoxComponent->mBox = Box { { 0, -1, 0 }, { 0.1, 1, 5.0 } };
			mBoxComponent->OnStart();

			mAlreadyTurned = true;
			mIsturning = false;
		}

		mTransform->RotateYaw(delta);
	}
}

void Door::OnCollide(Actor* collidedActor)
{
	Actor::OnCollide(collidedActor);

	DoomPlayer* player = dynamic_cast<DoomPlayer*>(collidedActor);
	if (player && !mAlreadyTurned)
	{
		mBoxComponent->OnEnd();
		mIsturning = true;
	}
}

void Door::SetPlayer(Actor* player)
{
	mPlayer = player;
}
