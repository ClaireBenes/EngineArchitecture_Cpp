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

	if (mIsturning)
	{
		float delta = -2.0f;
		mCurrentYaw += delta;

		if (mCurrentYaw <= -90.0f)
		{
			delta -= (mCurrentYaw + 90.0f);
			mIsturning = false;
		}

		mTransform->RotateYaw(delta);
	}
}

void Door::OnCollide(Actor* collidedActor)
{
	Actor::OnCollide(collidedActor);

	DoomPlayer* player = dynamic_cast<DoomPlayer*>(collidedActor);
	if (player)
	{
		mBoxComponent->OnEnd();
		mIsturning = true;
	}
}

void Door::SetPlayer(Actor* player)
{
	mPlayer = player;
}

float Door::GetYawFromQuaternion(const Quaternion& q)
{
	// Yaw (Y axis rotation)
	float siny_cosp = 2 * (q.w * q.y + q.z * q.x);
	float cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	return atan2(siny_cosp, cosy_cosp) * (180.0f / M_PI); // Convert to degrees
}
