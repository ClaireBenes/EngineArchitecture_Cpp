#include "ColliderComponent.h"

#include "Engine/Manager/PhysicManager.h"

ColliderComponent::ColliderComponent(Actor* pOwner):
Component(pOwner)
{
}

void ColliderComponent::OnStart()
{
	PhysicManager::Instance().AddComponent(this);
}
