#pragma once

#include "Engine/GameTool/Actor.h"

class MoveComponent;
class BoxColliderComponent;

class Pin : public Actor
{
public:
	void Start() override;
	void SetupComponents() override;
	void Update() override;

private:
	MoveComponent* moveComponent = nullptr;
	BoxColliderComponent* boxColliderComponent = nullptr;
};

