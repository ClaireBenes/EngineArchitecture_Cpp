#pragma once

#include "Engine/GameTool/Actor.h"

class RectangleColliderComponent;

class Bush : public Actor
{
public:
	void SetupComponents() override;
	void Update() override;
	void Destroy() override;

private:
	RectangleColliderComponent* colliderComponent = nullptr;
};

