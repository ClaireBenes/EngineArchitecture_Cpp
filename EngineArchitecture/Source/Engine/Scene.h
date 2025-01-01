#pragma once

#include <string>
#include <vector>

#include "SDL.h"

class Renderer;
class Window;
class Actor;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	//virtual functions
	virtual void Start() = 0;
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void OnInput(SDL_Event event) = 0;

	//non virtual functions
	void SetWindow(Window* pWindow);
	void SetRenderer(Renderer* pRenderer);

	void AddActor(Actor* pActor);
	void RemoveActor(Actor* pActor){};

protected:
	Window* mWindow;
	Renderer* mRenderer;
	std::vector<Actor*> mActors{};
};

