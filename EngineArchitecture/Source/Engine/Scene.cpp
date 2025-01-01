#include "Scene.h"

#include "Actor.h"

Scene::Scene()
{
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
	mActorList.push_back(pActor);
	pActor->SetScene(this);
}
