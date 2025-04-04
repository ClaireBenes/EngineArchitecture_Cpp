#pragma once

#include "../Component.h"
#include "Engine/GameTool/Utility/Maths.h"
#include "Engine/GameTool/Utility/Vector/Vector3.h"
#include "Engine/GameTool/Utility/Vector/Vector2.h"
#include "Engine/GameTool/Utility/Matrix/Matrix4.h"

class Transform : public Component
{
public:
	Transform(Actor* pOwner, Vector3 pPosition = Vector3::Zero, Vector3 pScale = Vector3::One, Quaternion pRotation = Quaternion::Identity);

	Vector3 Right() const { return Vector3::Transform(Vector3::Right, mRotation); }
	Vector3 Up() const { return Vector3::Transform(Vector3::Up, mRotation); }
	Vector3 Forward() const {return Vector3::Transform(Vector3::Forward, mRotation);}

	void ComputeWorldTransform();
	const Matrix4& GetWorldTransform() const;

	void LookAt(Vector3 target);

	//Rotation
	void RotatePitch(float degrees);
	void RotateYaw(float degrees);
	void RotateRoll(float degrees);

	Vector3 mPosition = Vector3::Zero;
	Vector3 mScale = Vector3::One;
	Quaternion mRotation = Quaternion::Identity;

private:
	Matrix4 mWorldTransform;
	bool NeedRecomputeWorldTransform = true;
};

