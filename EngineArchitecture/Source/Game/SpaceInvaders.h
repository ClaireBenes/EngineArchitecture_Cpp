#pragma once

#include "Engine/Scene.h"

class SpaceInvaders : public Scene
{
public:
	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;
	void OnInput(SDL_Event event) override;

private:
};

