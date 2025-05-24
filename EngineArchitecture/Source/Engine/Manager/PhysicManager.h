#pragma once

#include <vector>

class ColliderComponent;
class Vector3;

/**
 * @brief The PhysicManager is a singleton responsible for managing and detecting collisions
 * between ColliderComponent instances. 
 * It allows adding/removing components and performs collision detection between them.
 */
class PhysicManager
{
public: 
	// Constructor and destructor.
	PhysicManager(const PhysicManager&) = delete;
	PhysicManager& operator=(const PhysicManager&) = delete;

	/**
	 * @brief Returns the singleton instance of the PhysicManager.
	 * @return Reference to the static PhysicManager instance.
	 */
	static PhysicManager& Instance();

	/**
	 * @brief Adds a ColliderComponent to the manager for collision detection.
	 * @param pComponent The ColliderComponent to be added.
	 */
	void AddComponent(ColliderComponent* pComponent);
	/**
	 * @brief Removes a ColliderComponent from the manager.
	 * @param pComponent The ColliderComponent to be removed.
	 */
	void RemoveComponent(ColliderComponent* pComponent);

	/**
	 * @brief Performs collision detection with all other components and returns
	 * the first component that collides with the given one.
	 * @param pComponent The ColliderComponent to check collisions for.
	 * @return A pointer to the first colliding ColliderComponent or nullptr if none.
	 */
	ColliderComponent* Collision(ColliderComponent* pComponent);
	/**
	 * @brief Calculates the normal vector at the collision point between two components.
	 * @param A The first ColliderComponent.
	 * @param B The second ColliderComponent.
	 * @return The collision normal vector.
	 */
	Vector3 GetCollisionNormal(ColliderComponent* A, ColliderComponent* B);

private:
	/**
	 * @brief Private constructor to prevent instantiation (singleton-style).
	 */
	PhysicManager() {};

	/**
	 * @brief List of ColliderComponents for collision detection.
	 */
	std::vector<ColliderComponent*> colliderComponents;
};

