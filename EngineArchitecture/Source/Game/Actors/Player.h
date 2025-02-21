#pragma once

#include "Engine/GameTool/Actor.h"
#include "Engine/GameTool/Visual/Texture.h"

class RectangleColliderComponent;
class AnimatedSpriteRenderComponent;
class PlayerController;

class Player : public Actor
{
public:
	void SetupComponents() override;
	void Update() override;
	void Destroy() override;

private:

	void SetUpAnimations();

	RectangleColliderComponent* colliderComponent = nullptr;
	AnimatedSpriteRenderComponent* animatedSpriteComponent = nullptr;
};

