#pragma once

#include <string>

#include "Renderer.h"
#include "Window.h"

class Scene
{
public:
	Scene();

	//virtual functions
	virtual void Start(Renderer* pRenderer) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void OnInput(SDL_Event event) = 0;
	virtual void Close(){}

	//non virtual functions
	void SetWindow(Window* pWindow);

protected:
	Window* mWindow;
	Renderer* mRenderer;
};

