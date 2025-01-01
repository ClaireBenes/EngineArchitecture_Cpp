#pragma once

#include "Engine/Actor.h"

class Player : public Actor
{
public:
	void Start() override;
	void Update() override;
	void Destroy() override;
};

