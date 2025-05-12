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
	for(Actor * actor : mPendingActors)
	{
		mActors.emplace_back(actor);
		actor->Start();
	}
	mPendingActors.clear();

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

	//delete them when in dead state
	for (Actor* actor : mActorsToDelete)
	{
		RemoveActor(actor);
	}
	mActorsToDelete.clear();

	if (mShouldReload)
	{
		Reload();
	}
}

void Scene::SetWindow(Window* pWindow)
{
	mWindow = pWindow;
}

Window* Scene::GetWindow()
{
	return mWindow;
}

void Scene::SetRenderer(IRenderer* pRenderer)
{
	mRenderer = pRenderer;
}

IRenderer* Scene::GetRenderer()
{
	return mRenderer;
}

void Scene::Reload()
{
	// Defer reload for the end of tick
	if (mIsUpdatingActors)
	{
		mShouldReload = true;
		return;
	}

	// Destroy all actors
	while (!mActors.empty())
	{
		Actor* actor = mActors[mActors.size() - 1];
		RemoveActor(actor);
	}

	// Destroy all pending actors
	while (!mPendingActors.empty())
	{
		Actor* actor = mPendingActors[mPendingActors.size() - 1];
		RemoveActor(actor);
	}

	// We don't need to destroy all actors-to-delete since it should be destroyed
	// before the call in the Update.

	// Reload scene
	Start();

	mShouldReload = false;
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
		delete mPendingActors[mPendingActors.size() - 1];
		mPendingActors.pop_back();
	}

	it = find(mActors.begin(), mActors.end(), pActor);
	if (it != mActors.end())
	{
		std::iter_swap(it, mActors.end() - 1);
		delete mActors[mActors.size() - 1];
		mActors.pop_back();
	}
}
