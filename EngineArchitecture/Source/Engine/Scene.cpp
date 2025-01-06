#include "Scene.h"

#include "Renderer.h"
#include "Window.h"
#include "Actor.h"

//On destruction
Scene::~Scene()
{
	//Delete all actors
	for(Actor* actor : mActors)
	{
		delete actor;
	}
}

void Scene::Update(float deltaTime)
{
	for(Actor* actor : mActors)
	{
		actor->Update();
	}
}

void Scene::Render()
{
	for(Actor* actor : mActors)
	{
		actor->Render(mRenderer);
	}
}

void Scene::SetWindow(Window* pWindow)
{
	mWindow = pWindow;
}

void Scene::SetRenderer(Renderer* pRenderer)
{
	mRenderer = pRenderer;
}

void Scene::AddActor(Actor* pActor)
{
	//Add actor, give them the scene reference and start it
	mActors.push_back(pActor);
	pActor->SetScene(this);
	pActor->Start();
}
