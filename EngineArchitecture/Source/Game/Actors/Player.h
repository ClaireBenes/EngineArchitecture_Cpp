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

	RectangleColliderComponent* colliderComponent = nullptr;
	AnimatedSpriteRenderComponent* animatedSpriteComponent = nullptr;
	PlayerController* playerController = nullptr;
	std::vector<Texture> allTextures;
};

