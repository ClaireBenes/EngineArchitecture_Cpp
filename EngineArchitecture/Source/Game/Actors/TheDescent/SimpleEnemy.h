#pragma once

#include "Engine/GameTool/Actor.h"

class BoxColliderComponent;
class MeshComponent;
class MoveComponent;

class SimpleEnemy : public Actor
{
public:
	void Start() override;
	void SetupComponents() override;
	void Update() override;

	void SetTextureIndex(size_t newIndex);

	void TakeDamage(float damage);

private:
	BoxColliderComponent* mBoxComponent = nullptr;
	MeshComponent* mMeshComponent = nullptr;
	MoveComponent* moveComponent = nullptr;

	size_t mTextureIndex = 0;
	
	//damage
	const float mDamageDelay = 0.3f;
	float mCurrentDamageDelay = mDamageDelay;
	float mHealth = 2.0f;

	bool mIsTakingDamage = false;
};

