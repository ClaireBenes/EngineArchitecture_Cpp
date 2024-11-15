#include "Actor.h"

void Actor::AddComponent(Component* rComponent)
{
	mComponentList.push_back(rComponent);
}
