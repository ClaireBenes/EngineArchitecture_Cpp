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
