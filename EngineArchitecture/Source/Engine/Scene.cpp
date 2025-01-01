#include "Scene.h"

#include "Renderer.h"
#include "Window.h"
#include "Actor.h"

Scene::Scene()
{
}

Scene::~Scene()
{
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
	mActors.push_back(pActor);
	pActor->SetScene(this);
	pActor->Start();
}
