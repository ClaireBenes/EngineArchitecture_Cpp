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

	//Life
	void TakeDamage(int damage);
	void RestoreHealth();

	//Hud
	void AddHUDHeart(float xPos, float yPos = 300);
	void AddHUDRock(float xPos, float yPos);

	int GetAmmo();
	void Shoot();

private:
	Camera* mCamera = nullptr;
	FPSController* mMoveComponent = nullptr;
	BoxColliderComponent* mBoxComponent = nullptr;

	std::vector<Actor*> mAllHearts;
	std::vector<Actor*> mAllAmmos;

	const int mMaxHealth = 3;
	int mHealth = mMaxHealth;

	const int mAmmoPerLines = 10;
	const int mMaxAmmo = 20;
	int mAmmo = mMaxAmmo;

};

