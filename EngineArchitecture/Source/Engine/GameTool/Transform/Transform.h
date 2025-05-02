#pragma once

#include "../Component.h"
#include "Engine/GameTool/Utility/Maths.h"
#include "Engine/GameTool/Utility/Vector/Vector3.h"
#include "Engine/GameTool/Utility/Vector/Vector2.h"
#include "Engine/GameTool/Utility/Matrix/Matrix4.h"

/*
Transform is a component that defines the position, rotation, and scale of an actor in 3D space.
It provides direction vectors, transformation matrix computation, and rotation utility functions.
 */
class Transform : public Component
{
public:
	/*
	 * Constructor for Transform.
	 * @param pOwner The actor that owns this transform component.
	 * @param pPosition The initial position of the actor in 3D space (default: Vector3::Zero).
	 * @param pScale The initial scale of the actor (default: Vector3::One).
	 * @param pRotation The initial rotation of the actor (default: Quaternion::Identity).
	 */
	Transform(Actor* pOwner, Vector3 pPosition = Vector3::Zero, Vector3 pScale = Vector3::One, Quaternion pRotation = Quaternion::Identity);

	/*
	 * Returns the right direction vector of the object (transformed by its current rotation).
	 * @return Vector representing the right direction in the world space.
	 */
	Vector3 Right() const { return Vector3::Transform(Vector3::Right, mRotation); }
	/*
	 * Returns the up direction vector of the object (transformed by its current rotation).
	 * @return Vector representing the up direction in the world space.
	 */
	Vector3 Up() const { return Vector3::Transform(Vector3::Up, mRotation); }
	/*
	 * Returns the forward direction vector of the object (transformed by its current rotation).
	 * @return Vector representing the forward direction in the world space.
	 */
	Vector3 Forward() const {return Vector3::Transform(Vector3::Forward, mRotation);}


	/*
	Computes the world transformation matrix (position, rotation, scale).
	This is used to update the object's global transformation matrix.
	 */
	void ComputeWorldTransform();
	/*
	 * Gets the world transformation matrix for this transform.
	 * @return Reference to the world transformation matrix.
	 */
	const Matrix4& GetWorldTransform() const;

	/*
	 * Makes the object rotate to face a given target position.
	 * @param target The position to look at.
	 */
	void LookAt(Vector3 target);

	// Rotation methods that apply rotations around the specific axes:
	/*
	 * Rotates the object around the pitch axis (X-axis).
	 * @param The number of degrees to rotate around the pitch axis.
	 */
	void RotatePitch(float degrees);
	/*
	 * Rotates the object around the yaw axis (Y-axis).
	 * @param The number of degrees to rotate around the yaw axis.
	 */
	void RotateYaw(float degrees);
	/*
	 * Rotates the object around the roll axis (Z-axis).
	 * @param The number of degrees to rotate around the roll axis.
	 */
	void RotateRoll(float degrees);

	// Variables for position, scale, and rotation
	Vector3 mPosition = Vector3::Zero; // Position of the object in 3D space
	Vector3 mScale = Vector3::One; // Scale of the object in 3D space

	Quaternion mRotation = Quaternion::Identity; //Rotation of the object (in quaternion form)

private:
	Matrix4 mWorldTransform; // The world transformation matrix of the object (combines position, scale, and rotation)
	bool NeedRecomputeWorldTransform = true; // Flag to indicate if the world transform needs recomputation
};

