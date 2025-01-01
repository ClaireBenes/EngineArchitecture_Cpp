#pragma once

#include <string>
#include <vector>

#include "Renderer.h"
#include "Window.h"

class Actor;

class Scene
{
public:
	Scene();

	//virtual functions
	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void OnInput(SDL_Event event) = 0;
	virtual void Close(){}

	//non virtual functions
	void SetWindow(Window* pWindow);
	void SetRenderer(Renderer* pRenderer);

	void AddActor(Actor* pActor);
	void RemoveActor(Actor* pActor);

protected:
	Window* mWindow;
	Renderer* mRenderer;
	std::vector<Actor*> mActorList{};
};

