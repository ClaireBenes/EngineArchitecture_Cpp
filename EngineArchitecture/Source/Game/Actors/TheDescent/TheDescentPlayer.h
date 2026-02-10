#pragma once

#include "Engine/GameTool/Actor.h"
#include "Engine/GameTool/Camera.h"
#include "Engine/Shader/ShaderProgram.h"

#include <vector>

class PilotController;
class BoxColliderComponent;
class SpriteRenderComponent;
class ScreenEffectRenderComponent;

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
	PilotController* mMoveComponent = nullptr;

	BoxColliderComponent* mBoxComponent = nullptr;
	SpriteRenderComponent* loseScreen = nullptr;
	SpriteRenderComponent* winScreen = nullptr;

	// Post Process Shaders
	ScreenEffectRenderComponent* mGodRayScreenEffect = nullptr;
	ScreenEffectRenderComponent* mDistortionScreenEffect = nullptr;

	std::vector<Actor*> mAllHearts;

	//Heart
	const int mMaxHealth = 3;
	int mHealth = mMaxHealth;
};

