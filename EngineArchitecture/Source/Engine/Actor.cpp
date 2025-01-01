#include "Actor.h"

Actor::Actor()
{

}

void Actor::Start()
{
	SetupComponents();

	for(Component* myComponent : mComponentList)
	{
		myComponent->OnStart();
	}
}

void Actor::SetScene(Scene* pScene)
{
	mScene = pScene;
}

void Actor::AddComponent(Component* pComponent)
{
	mComponentList.push_back(pComponent);
}

void Actor::RemoveComponent(Component* pComponent)
{
	mComponentList.erase(mComponentList.begin() + pComponent->GetUpdateOrder());
}

void Actor::SetActive(bool isActive)
{
	if(isActive)
	{
		mState = ActorState::Active;
	}
	else
	{
		mState = ActorState::Paused;
	}

	for(Component* myComponent : mComponentList)
	{
		myComponent->SetActive(isActive);
	}
}

void Actor::Update()
{
	for(Component* myComponent : mComponentList)
	{
		myComponent->Update();
	}
}

void Actor::Destroy()
{
	for(Component* myComponent : mComponentList)
	{
		myComponent->OnEnd();
	}
}
