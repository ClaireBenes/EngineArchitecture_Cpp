#pragma once

#include "Scene.h"
#include "Transform/Transform.h"
#include "Component.h"
#include "Engine/Time.h"

#include <vector>

class RenderComponent;
class ColliderComponent;
class AssetManager;

/**
 * @brief All actor possible state
 */
enum class ActorState
{
	/**
	 * @brief Actor is active and updated/rendered
	 */
	Active,
	/**
	 * @brief Actor is paused, not updated/rendered
	 */
	Paused,
	/**
	 * @brief Actor is marked for destruction
	 */
	Dead
};

/**
 * @brief Base class representing an actor in the scene.
 *
 * Actors are entities that can contain multiple components such as renderers, colliders, etc.
 * They manage their own lifecycle (setup, start, update, destroy) and interact with the scene.
 */
class Actor
{
public:
	Actor();
	virtual ~Actor();

	// Functions

	/**
	 * @brief Sets the scene for this actor.
	 * @param pScene The scene this actor belongs to.
	 */
	void SetScene(Scene* pScene);

	/**
	 * @brief Adds a component to the actor.
	 * The component can be of various types (render, collider, etc.).
	 * @param pComponent The component to add to the actor.
	 */
	void AddComponent(Component* pComponent);

	/**
	 * @brief Removes a specific component from the actor.
	 * @param pComponent The component to remove.
	 */
	void RemoveComponent(Component* pComponent);

	/**
	 * @brief Updates all components' world transforms.
	 */
	void UpdateComponentsTransform();

	/**
	 * @brief Sets the actor's active state, enabling or disabling components accordingly.
	 * @param isActive True to activate the actor, false to pause it.
	 */
	void SetActive(bool isActive);

	/**
	 * @brief Returns the current state of the actor (Active, Paused, Dead).
	 * @return The actor's state.
	 */
	ActorState GetState() const;

	/**
	 * @brief Returns the position of the actor in world space.
	 * @return The actor's position.
	 */
	Vector3 GetPosition() const;

	/**
	 * @brief Called to set up the actor's components after initialization.
	 */
	virtual void SetupComponents() {};

	/**
	 * @brief Called once at the start of the scene, after setup.
	 */
	virtual void Start();

	/**
	 * @brief Called every frame to update the actor and its component.
	 */
	virtual void Update();

	/**
	 * @brief Called to destroy the actor, marking it as dead.
	 */
	virtual void Destroy();

	/**
	 * @brief Called when this actor collides with another actor.
	 * Override this to handle collision behavior.
	 * @param collidedActor The actor that collided with this actor.
	 */
	virtual void OnCollide(Actor* collidedActor) {};

public:
	//Variables

	/** 
	 * @brief Transform representing position, rotation, scale
	 */
	Transform* mTransform =  nullptr; 
	/**
	 * @brief Scene this actor belongs to
	 */
	Scene* mScene = nullptr;

	/**
	 * @brief Gets a component of a specific type attached to this actor.
	 * @param C The type of component to retrieve.
	 * @return Pointer to the component if found, nullptr otherwise.
	 */
	template<typename  C>
	C* GetComponentOfType() const
	{
		C* result = nullptr;
		for (Component* component : mComponents)
		{
			result = dynamic_cast<C*>(component);
			if (result != nullptr) return result;
		}
		return nullptr;
	}

private:
	/**
	 * @brief Actor's current state (Active, Paused, Dead)
	 */
	ActorState mState = ActorState::Paused;

	// Component lists
	std::vector<Component*> mComponents{};
	std::vector<RenderComponent*> mRenderComponents{};
	std::vector<ColliderComponent*> mColliderComponents{};
};




