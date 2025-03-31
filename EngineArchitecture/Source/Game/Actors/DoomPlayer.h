#pragma once
#include "Engine/GameTool/Actor.h"
#include "Engine/GameTool/Camera.h"

class DoomPlayer : public Actor
{
public:
	void Start() override;
	void SetupComponents() override;
	void Update() override;

private:
	Camera* mCamera = nullptr;
};

