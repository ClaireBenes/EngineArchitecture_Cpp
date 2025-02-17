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
	virtual void Load() {};
	virtual void Start() = 0;
	virtual void Update(float deltaTime);
	virtual void Render();

	//Non virtual functions
	void SetWindow(Window* pWindow);
	void SetRenderer(Renderer* pRenderer);
	Renderer* GetRenderer();

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

