#pragma once

#include <vector>

class ColliderComponent;

class PhysicManager
{
public:
	PhysicManager(const PhysicManager&) = delete;
	PhysicManager& operator=(const PhysicManager&) = delete;

	static PhysicManager& Instance();

	void AddComponent(ColliderComponent* pComponent);
	void RemoveComponent(ColliderComponent* pComponent);

	ColliderComponent* Collision(ColliderComponent* pComponent);

private:
	PhysicManager() {};
	std::vector<ColliderComponent*> colliderComponents;
};

