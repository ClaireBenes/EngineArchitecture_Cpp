#pragma once

#include "Engine/GameTool/Scene.h"

class Mesh;
class DoomPlayer;

class Doom : public Scene
{
public:
	void Load() override;
	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;

private:
	DoomPlayer* mPlayer = nullptr;
	Mesh* mFloorMesh = nullptr;
	Mesh* mFirstEnemy = nullptr;
};

