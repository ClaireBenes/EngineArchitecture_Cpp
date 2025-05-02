#pragma once

#include "Engine/GameTool/Actor.h"
#include "Engine/GameTool/Camera.h"
#include <vector>

class FPSController;
class BoxColliderComponent;

class DoomPlayer : public Actor
{
public:
	void Start() override;
	void SetupComponents() override;
	void Update() override;

	void TakeDamage(int damage);

private:
	Camera* mCamera = nullptr;
	FPSController* mMoveComponent = nullptr;
	BoxColliderComponent* mBoxComponent = nullptr;

	std::vector<Actor*> mAllHearts;
	int mHealth = 3;

};

