#pragma once

#include "Engine/GameTool/Actor.h"
#include "Game/Actors/Doom/DoomPlayer.h"

class MoveComponent;
class DoomPlayer;

class FirstEnemy : public Actor
{
public:
	void Start() override;
	void SetupComponents() override;
	void Update() override;

	void SetPlayer(DoomPlayer* pNewPlayer);

private:
	MoveComponent* moveComponent = nullptr;
	DoomPlayer* mPlayer = nullptr;
};

