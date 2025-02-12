#include "PhysicManager.h"

#include "../GameTool/Collision/ColliderComponent.h"

PhysicManager& PhysicManager::Instance()
{
    static PhysicManager physicManager;
    return physicManager;
}

void PhysicManager::AddComponent(ColliderComponent* pComponent)
{
    colliderComponents.push_back(pComponent);
}

void PhysicManager::RemoveComponent(ColliderComponent* pComponent)
{
    auto it = std::find(colliderComponents.begin(), colliderComponents.end(), pComponent);

    if(it != colliderComponents.end())
    {
        colliderComponents.erase(it);
    }
}

bool PhysicManager::Collision(ColliderComponent* pComponent)
{
    for(ColliderComponent* pCollider : colliderComponents)
    {
        if((pCollider != pComponent) && (pCollider->Collision(pComponent)))
        {
            return true;
        }
    }
    return false;
}
