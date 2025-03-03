#include "Component.h"
#include "Actor.h"

Component::Component(int pUpdateOrder) : mUpdateOrder(pUpdateOrder)
{
}

void Component::SetActive(bool isActive)
{
	mIsActive = isActive;
}

//Put component on actor
void Component::SetOwner(Actor* pOwner)
{
	mOwner = pOwner;
	mOwner->AddComponent(this);
}

int Component::GetUpdateOrder() const
{
	return mUpdateOrder;
}
