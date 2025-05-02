#pragma once

#include "Engine/GameTool/Actor.h"

class BoxColliderComponent;
class MoveComponent;

class Projectile : public Actor
{
public:
	void Start() override;
	void SetupComponents() override;
	void Update() override;

	void OnCollide(Actor* collidedActor) override;
	void SetPlayer(Actor* player);

private:
	MoveComponent* mMoveComponent = nullptr;
	Actor* mPlayer = nullptr;
};

