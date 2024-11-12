#pragma once

#include "Scene.h"
#include "Renderer.h"

class Pong : public Scene
{
public:
	Pong();

	void Start(Renderer* pRenderer) override;
	void Update(float deltaTime) override;
	void Render() override;
	void OnInput(SDL_Event) override;
	void Close() override;

private:
	Renderer* mRenderer{};
};

