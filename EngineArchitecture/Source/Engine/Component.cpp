#include "Component.h"
#include "Actor.h"

Component::Component(Actor* pOwner, float pUpdateOrder) : mOwner(*pOwner), mUpdateOrder(pUpdateOrder)
{
	mOwner.AddComponent(this);
}
