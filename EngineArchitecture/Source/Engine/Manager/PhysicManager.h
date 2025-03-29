#pragma once

#include <vector>

class ColliderComponent;
class Vector3;

class PhysicManager
{
public:
	PhysicManager(const PhysicManager&) = delete;
	PhysicManager& operator=(const PhysicManager&) = delete;

	static PhysicManager& Instance();

	void AddComponent(ColliderComponent* pComponent);
	void RemoveComponent(ColliderComponent* pComponent);

	ColliderComponent* Collision(ColliderComponent* pComponent);
	Vector3 GetCollisionNormal(ColliderComponent* A, ColliderComponent* B);

private:
	PhysicManager() {};
	std::vector<ColliderComponent*> colliderComponents;
};

