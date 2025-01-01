#include "Component.h"
#include "Actor.h"

Component::Component(float pUpdateOrder) : mUpdateOrder(pUpdateOrder)
{
}

Component::~Component()
{
	if(mOwner != nullptr)
	{
		mOwner->RemoveComponent(this);
	}
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

void Component::SetOwner(Actor* pOwner)
{
	mOwner = pOwner;
	mOwner->AddComponent(this);
}

int Component::GetUpdateOrder() const
{
	return mUpdateOrder;
}
