#include "ColliderComponent.h"

#include "../../PhysicManager.h"

void ColliderComponent::OnStart()
{
	PhysicManager::Instance().AddComponent(this);
}

void ColliderComponent::OnEnd()
{
	PhysicManager::Instance().RemoveComponent(this);
}
