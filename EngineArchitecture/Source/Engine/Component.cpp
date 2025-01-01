#include "Component.h"
#include "Actor.h"

Component::Component(Actor* pOwner, float pUpdateOrder) : mOwner(*pOwner), mUpdateOrder(pUpdateOrder)
{
	mOwner.AddComponent(this);
}

Component::~Component()
{
	mOwner.RemoveComponent(this);
}

void Component::OnStart()
{
	//to add
}

void Component::Update()
{
	//to add
}

void Component::OnEnd()
{
	//to add
}

void Component::SetActive(bool isActive)
{
	mIsActive = isActive;
}

int Component::GetUpdateOrder() const
{
	return mUpdateOrder;
}
