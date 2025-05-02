#include "Scene.h"

#include "../Manager/AssetManager.h"
#include "Engine/Renderer/IRenderer.h"
#include "../Window.h"
#include "Actor.h"

#include <algorithm>


Scene::Scene() : mRenderer(nullptr), mWindow(nullptr)
{
}

//On destruction
Scene::~Scene()
{
	//Delete all actors
	for(Actor* actor : mActors)
	{
		delete actor;
	}

	//Free up resources
	AssetManager::Clear();
}

void Scene::Update(float deltaTime)
{
	mIsUpdatingActors = true;

	for(Actor* actor : mActors)
	{
		actor->Update();
		if (actor->GetState() == ActorState::Dead)
		{
			mActorsToDelete.push_back(actor);
		}
	}

	mIsUpdatingActors = false;

	for(Actor * actor : mPendingActors)
	{
		mActors.emplace_back(actor);
		actor->Start();
	}

	mPendingActors.clear();

	//delete them when in dead state
	for (Actor* actor : mActorsToDelete)
	{
		RemoveActor(actor);
		delete actor;
	}

	mActorsToDelete.clear();
}

void Scene::SetWindow(Window* pWindow)
{
	mWindow = pWindow;
}

void Scene::SetRenderer(IRenderer* pRenderer)
{
	mRenderer = pRenderer;
}

IRenderer* Scene::GetRenderer()
{
	return mRenderer;
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
