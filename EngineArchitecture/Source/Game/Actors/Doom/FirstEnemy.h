#pragma once

#include "Engine/GameTool/Actor.h"
#include "Game/Actors/Doom/DoomPlayer.h"

class BoxColliderComponent;
class MoveComponent;
class DoomPlayer;

class FirstEnemy : public Actor
{
public:
	void Start() override;
	void SetupComponents() override;
	void Update() override;

	void SetPlayer(DoomPlayer* pNewPlayer);

	float health = 5.0f;

private:
	BoxColliderComponent* boxComponent = nullptr;
	MoveComponent* moveComponent = nullptr;
	DoomPlayer* mPlayer = nullptr;
};

