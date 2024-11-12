#pragma once

#include "Scene.h"
#include "Renderer.h"

class Pong : public Scene
{
public:
	Pong();

	void Start(Renderer* pRenderer) override;
	void Update() override;
	void Render() override;
	void OnInput(SDL_Event) override;
	void Close() override;

private:
	Renderer* mRenderer{};
};

