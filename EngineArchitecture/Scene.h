#pragma once

#include <string>

#include "Renderer.h"

class Scene
{
public:
	Scene();

	virtual void Start(Renderer* pRenderer) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void OnInput(SDL_Event event) = 0;
	virtual void Close() = 0;

private:
	std::string mTitle = "Scene";
	Renderer* mRenderer;

};

