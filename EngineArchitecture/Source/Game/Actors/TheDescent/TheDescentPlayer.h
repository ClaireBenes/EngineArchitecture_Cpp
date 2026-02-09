#pragma once

#include "Engine/GameTool/Actor.h"
#include "Engine/GameTool/Camera.h"
#include <vector>

class EditorController;
class BoxColliderComponent;
class SpriteRenderComponent;
class Mesh;

class TheDescentPlayer : public Actor
{
public:
	void Start() override;
	void SetupComponents() override;
	void Update() override;

	void EndGame(bool isWin);

	//Life
	void TakeDamage(int damage);

	void Shoot();

public:
	bool mIsGameEnd = false;

private:
	Camera* mCamera = nullptr;
	EditorController* mMoveComponent = nullptr;

	BoxColliderComponent* mBoxComponent = nullptr;
	SpriteRenderComponent* loseScreen = nullptr;
	SpriteRenderComponent* winScreen = nullptr;

	Mesh* mGodRayMesh = nullptr;
	Actor* mGodsRay = nullptr;

	std::vector<Actor*> mAllHearts;

	//Heart
	const int mMaxHealth = 3;
	int mHealth = mMaxHealth;
};

