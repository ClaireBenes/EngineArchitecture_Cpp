#pragma once

#include "Engine/GameTool/Actor.h"

class BoxColliderComponent;
class MoveComponent;

class EnemyProjectile : public Actor
{
public:
	void Start() override;
	void SetupComponents() override;
	void Update() override;

	void OnCollide(Actor* collidedActor) override;

	void SetEnemy(Actor* enemy);

private:
	MoveComponent* mMoveComponent = nullptr;
	Actor* mEnemy = nullptr;
};

