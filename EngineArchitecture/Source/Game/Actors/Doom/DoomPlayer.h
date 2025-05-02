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
	void RestoreHealth();

private:
	Camera* mCamera = nullptr;
	FPSController* mMoveComponent = nullptr;
	BoxColliderComponent* mBoxComponent = nullptr;

	std::vector<Actor*> mAllHearts;

	const int mMaxHealth = 3;
	int mHealth = mMaxHealth;

};

