#pragma once

#include "Scene.h"
#include "Transform/Transform.h"
#include "Component.h"
#include "Engine/Time.h"

#include <vector>

class RenderComponent;
class ColliderComponent;
class AssetManager;

//All actor possible state
enum class ActorState
{
	Active,   // Actor is active and updated/rendered
	Paused,   // Actor is paused, not updated/rendered
	Dead      // Actor is marked for destruction
};


class Actor
{
public:
	Actor();
	virtual ~Actor();

	// Functions

	/*
	 * Sets the scene for this actor.
	 * @param pScene The scene this actor belongs to.
	 */
	void SetScene(Scene* pScene);

	/*
	 * Adds a component to the actor.
	 * The component can be of various types (render, collider, etc.).
	 * @param pComponent The component to add to the actor.
	 */
	void AddComponent(Component* pComponent);

	/*
	 * Removes a specific component from the actor.
	 * @param pComponent The component to remove.
	 */
	void RemoveComponent(Component* pComponent);

	/*
	Updates all components' world transforms.
	 */
	void UpdateComponentsTransform();

	/*
	 * Sets the actor's active state, enabling or disabling components accordingly.
	 * @param isActive True to activate the actor, false to pause it.
	 */
	void SetActive(bool isActive);

	/*
	 * Returns the current state of the actor (Active, Paused, Dead).
	 * @return The actor's state.
	 */
	ActorState GetState() const;

	/*
	 * Returns the position of the actor in world space.
	 * @return The actor's position.
	 */
	Vector3 GetPosition() const;

	/*
	Called to set up the actor's components after initialization.
	 */
	virtual void SetupComponents() {};

	/*
	Called once at the start of the scene, after setup.
	 */
	virtual void Start();

	/*
	Called every frame to update the actor and its component.
	 */
	virtual void Update();

	/*
	Called to destroy the actor, marking it as dead.
	 */
	virtual void Destroy();

	/*
	 * Called when this actor collides with another actor.
	 * Override this to handle collision behavior.
	 * @param collidedActor The actor that collided with this actor.
	 */
	virtual void OnCollide(Actor* collidedActor) {};

public:
	//Variables

	Transform* mTransform =  nullptr; //Transform representing position, rotation, scale
	Scene* mScene = nullptr; //Scene this actor belongs to

	/*
	 * Gets a component of a specific type attached to this actor.
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
	ActorState mState = ActorState::Paused; // Actor's current state (Active, Paused, Dead)

	// Component lists
	std::vector<Component*> mComponents{};
	std::vector<RenderComponent*> mRenderComponents{};
	std::vector<ColliderComponent*> mColliderComponents{};
};




