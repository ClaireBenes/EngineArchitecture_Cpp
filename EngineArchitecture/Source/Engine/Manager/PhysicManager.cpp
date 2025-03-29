#include "PhysicManager.h"

#include "../GameTool/Collision/ColliderComponent.h"

#include "Engine/GameTool/Utility/Vector/Vector3.h"
#include "Engine/GameTool/Actor.h"

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

ColliderComponent* PhysicManager::Collision(ColliderComponent* pComponent)
{
    for(ColliderComponent* pCollider : colliderComponents)
    {
        if((pCollider != pComponent) && (pCollider->Collision(pComponent)))
        {
            return pCollider;
        }
    }
    return nullptr;
}

Vector3 PhysicManager::GetCollisionNormal(ColliderComponent* A, ColliderComponent* B)
{
    if (!A || !B)
    {
        return Vector3(0, 0, 0);
    }

    Vector3 posA = A->GetOwner()->GetPosition();
    Vector3 posB = B->GetOwner()->GetPosition();

    Vector3 collisionNormal = (posB - posA).Normalized();

    return collisionNormal;
}
