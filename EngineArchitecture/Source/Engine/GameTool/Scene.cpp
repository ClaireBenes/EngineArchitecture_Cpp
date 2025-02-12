#include "Scene.h"

#include "../Manager/AssetManager.h"
#include "../Renderer.h"
#include "../Window.h"
#include "Actor.h"

#include <algorithm>


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
	mIsUpdatingActors = true;

	for(Actor* actor : mActors)
	{
		actor->Update();
	}

	mIsUpdatingActors = false;

	for(Actor * actor: mPendingActors)
	{
		mActors.emplace_back(actor);
		actor->Start();
	}

	mPendingActors.clear();

	//delete them when in dead state
}

void Scene::Render()
{
	for(Actor* actor : mActors)
	{
		actor->Render(mRenderer);
	}
}

void Scene::Unload()
{
	//Free actors pointers memory
   //Because ~Actor() calls RemoveActor, we have to use a while loop
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	//Free up resources
	AssetManager::Clear();

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
	pActor->SetScene(this);

	if (mIsUpdatingActors)
	{
		mPendingActors.emplace_back(pActor);
	}
	else
	{
		mActors.emplace_back(pActor);
		pActor->Start();
	}

}

void Scene::RemoveActor(Actor* pActor)
{
	std::vector<Actor*>::iterator it = find(mPendingActors.begin(), mPendingActors.end(), pActor);
	if (it != mPendingActors.end())
	{
		std::iter_swap(it, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	it = find(mActors.begin(), mActors.end(), pActor);
	if (it != mActors.end())
	{
		std::iter_swap(it, mActors.end() - 1);
		mActors.pop_back();
	}

}
