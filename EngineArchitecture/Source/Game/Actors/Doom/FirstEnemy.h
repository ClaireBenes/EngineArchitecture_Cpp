#pragma once

#include "Engine/GameTool/Actor.h"
#include "Game/Actors/Doom/DoomPlayer.h"

class BoxColliderComponent;
class MeshComponent;
class MoveComponent;
class DoomPlayer;

class FirstEnemy : public Actor
{
public:
	void Start() override;
	void SetupComponents() override;
	void Update() override;

	void SetPlayer(DoomPlayer* pNewPlayer);
	void SetTextureIndex(size_t newIndex);

	void TakeDamage(float damage);

private:
	BoxColliderComponent* boxComponent = nullptr;
	MeshComponent* mMeshComponent = nullptr;
	MoveComponent* moveComponent = nullptr;
	DoomPlayer* mPlayer = nullptr;

	size_t mTextureIndex = 0;

	const float mDamageDelay = 0.3f;
	float mCurrentDamageDelay = mDamageDelay;
	float mHealth = 5.0f;

	bool mIsTakingDamage = false;
};

