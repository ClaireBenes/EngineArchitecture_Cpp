#pragma once

#include "Engine/GameTool/Actor.h"
#include "Engine/GameTool/Visual/Texture.h"

class RectangleColliderComponent;
class AnimatedSpriteRenderComponent;

class Player : public Actor
{
public:
	void SetupComponents() override;
	void Update() override;
	void Destroy() override;

	void StopMoving();

	//for movement
	bool mIsMovingUp = false;
	bool mIsMovingDown = false;
	bool mIsMovingRight = false;
	bool mIsMovingLeft = false;

private:
	float mSpeedX = 100;
	float mSpeedY = 100;

	RectangleColliderComponent* colliderComponent = nullptr;
	AnimatedSpriteRenderComponent* animatedSpriteComponent = nullptr;
	std::vector<Texture> allTextures;
};

