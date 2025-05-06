#pragma once

#include "Engine/GameTool/Actor.h"

class AmmoPickUp : public Actor
{
public:
	void Start() override;
	void SetupComponents() override;
	void Update() override;

	void OnCollide(Actor* collidedActor) override;
	void SetPlayer(Actor* player);

private:
	Actor* mPlayer = nullptr;
};



