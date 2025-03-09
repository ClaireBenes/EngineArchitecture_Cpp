#pragma once

#include "../Component.h"
#include "Engine/GameTool/Utility/Maths.h"
#include "Engine/GameTool/Utility/Vector/Vector3.h"
#include "Engine/GameTool/Utility/Vector/Vector2.h"
#include "Engine/GameTool/Utility/Matrix/Matrix4.h"

class Transform : public Component
{
public:
	Transform(Vector3 pPosition = Vector3::Zero, Vector3 pScale = Vector3::One, float pRotation = 0.0f);

	Vector3 Right() const { return Vector3(Maths::Cos(mRotation.z), -Maths::Sin(mRotation.z), 0); }
	Vector3 Up() const { return Vector3(Maths::Sin(mRotation.z), -Maths::Cos(mRotation.z), 0); }
	//Vector3 Forward() const {return Vector3::Transform(Vector3::unitX, mRotation);}
	Vector3 Forward() const { return Vector3::Zero; }

	void ComputeWorldTransform();
	const Matrix4& GetWorldTransform() const;

	Vector3 mPosition = Vector3::Zero;
	Vector3 mScale = Vector3::One;
	Vector3 mRotation = Vector3::Zero;

private:
	Matrix4 mWorldTransform;
	bool NeedRecomputeWorldTransform = true;
};

