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
	Scene(){};
	virtual ~Scene();

	//Virtual functions
	virtual void Start() = 0;
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void OnInput(SDL_Event event) = 0;

	//Non virtual functions
	void SetWindow(Window* pWindow);
	void SetRenderer(Renderer* pRenderer);

	void AddActor(Actor* pActor);
	void RemoveActor(Actor* pActor);

protected:
	//Variables
	Window* mWindow;
	Renderer* mRenderer;
	std::vector<Actor*> mActors{};

private:
	std::vector<Actor*> mPendingActors {};

	bool mIsUpdatingActors = false;
};

