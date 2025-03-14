#pragma once

#include "Engine/GameTool/Actor.h"

class Mesh;

class Wall : public Actor
{
public:
	void Start() override;
	void SetupComponents() override;
	void Update() override;
	void Destroy() override;

private:
	Mesh* mPinMesh = nullptr;
};

