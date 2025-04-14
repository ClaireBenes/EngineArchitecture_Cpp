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

private:
	MoveComponent* moveComponent = nullptr;
};

