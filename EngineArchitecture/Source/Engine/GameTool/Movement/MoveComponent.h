#pragma once

#include "Engine/GameTool/Component.h"
#include "Engine/GameTool/Utility/Vector/Vector3.h"

class ColliderComponent;

/*
MoveComponent handles the movement logic for an actor.
It applies forces, updates position and rotation, and integrates basic physics like gravity and friction.
Also supports collision detection via an optional collider component.
 */
class MoveComponent : public Component
{
public:
	/*
	 * Constructor for MoveComponent.
	 * @param pOwner The actor that owns this component.
	 * @param pUpdateOrder Order in which the component will be updated (default: 100).
	 */
	MoveComponent(Actor* pOwner, int pUpdateOrder = 100);

	// Deleted default constructor and copy functions
	MoveComponent() = delete;
	MoveComponent(const MoveComponent&) = delete;
	MoveComponent& operator= (const MoveComponent&) = delete;

	/*
	 * Gets the current speed of the actor.
	 * @return The actor's speed in 3D space as a Vector3.
	 */
	Vector3 GetSpeed() const;
	/*
	 * Sets the actor's speed.
	 * @param pSpeed New speed to be set.
	 */
	void SetSpeed(Vector3 pSpeed);

	/*
	 * Adds a force to the actor's velocity.
	 * @param pForce The force to add to the velocity.
	 */
	void AddForce(Vector3 pForce);


	/*
	 * Gets the current rotation speed of the actor.
	 * @return The actor's rotation speed as a Vector2 (x for yaw, y for pitch).
	 */
	Vector2 GetRotationSpeed() const;
	/*
	 * Sets the rotation speed of the actor.
	 * @param pRotationSpeed The new rotation speed to set.
	 */
	void SetRotationSpeed(Vector2 pRotationSpeed);


	/*
	 * Updates the position, rotation, and velocity of the actor each frame.
	 * Applies gravity, friction, rotation, and checks for collisions.
	 */
	virtual void Update() override;
	/*
	 * Computes the desired position of the actor after applying speed and velocity.
	 * Also handles collision detection along the X, Y, and Z axes.
	 * @return The calculated desired position after checking for collisions.
	 */
	virtual Vector3 GetDesiredPos();

	/*
	 * Sets the collider for collision detection.
	 * @param pCollider Collider component to be used for collision checks.
	 */
	void SetCollider(ColliderComponent* pCollider);

	/*
	 * Checks for a collision with other colliders in the scene.
	 * If a collision is detected, applies a simple collision response.
	 * @return The collider component that was collided with, or nullptr if no collision.
	 */
	ColliderComponent* CheckCollision();

	// Variables for gravity, velocity, friction, and speed:
	Vector3 mGravityDirection = Vector3::Zero; // Direction of gravity (set to zero by default).
	Vector3 mVelocity = Vector3::Zero; // Velocity of the actor in 3D space.

	float mFriction = 0.8f; // Friction factor applied to the velocity.

protected:
	Vector3 mSpeed = 0; // Speed of the actor in 3D space (can be adjusted to control movement).
	Vector2 mRotationSpeed = 0; // Rotation speed of the actor (yaw and pitch).

private:
	ColliderComponent* mCollidercomponent = nullptr; // Collider component used for collision checks.
};

