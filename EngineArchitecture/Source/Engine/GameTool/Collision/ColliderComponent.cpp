#include "ColliderComponent.h"

#include "Engine/Manager/PhysicManager.h"

void ColliderComponent::OnStart()
{
	PhysicManager::Instance().AddComponent(this);
}

void ColliderComponent::OnEnd()
{
	//PhysicManager::Instance().RemoveComponent(this);
}
