#pragma once

#include "Engine/GameTool/Actor.h"
#include "Engine/GameTool/Camera.h"
#include <vector>

class FPSController;
class BoxColliderComponent;
class SpriteRenderComponent;

class DoomPlayer : public Actor
{
public:
	void Start() override;
	void SetupComponents() override;
	void Update() override;

	void EndGame(bool isWin);

	//Life
	void TakeDamage(int damage);
	void RestoreHealth();

	//Hud
	void AddHUDHeart(float xPos, float yPos = 300);
	void AddHUDRock(float xPos, float yPos);

	//Ammo
	int GetAmmo();
	void RestoreAmmo();
	void Shoot();

public:
	bool mIsGameEnd = false;

private:
	Camera* mCamera = nullptr;
	FPSController* mMoveComponent = nullptr;

	BoxColliderComponent* mBoxComponent = nullptr;
	SpriteRenderComponent* loseScreen = nullptr;
	SpriteRenderComponent* winScreen = nullptr;


	std::vector<Actor*> mAllHearts;
	std::vector<Actor*> mAllAmmos;

	//Heart
	const int mHeartXOffset = 100;

	const int mMaxHealth = 3;
	int mHealth = mMaxHealth;

	//Ammo
	const int mAmmoPerLines = 10;
	const int mAmmoXOffset = 30;
	const int mAmmoYOffset = 40;

	const int mAmmoXPos = -600;
	const int mAmmoYPos = -320;

	const int mAmmoToPickUp = 5;

	const int mMaxAmmo = 20;
	int mAmmo = mMaxAmmo;
};

