#include "Actor.h"

void Actor::AttachScene(Scene* rScene)
{
	mScene = rScene;
}

void Actor::AddComponent(Component* rComponent)
{
	mComponentList.push_back(rComponent);
}

void Actor::RemoveComponent(Component* rComponent)
{
	mComponentList.erase(mComponentList.begin()+rComponent->GetUpdateOrder());
}

void Actor::SetActive()
{
	for (Component* myComponent : mComponentList) 
	{
		myComponent->OnStart();
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
