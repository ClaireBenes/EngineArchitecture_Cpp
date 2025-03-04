#pragma once

#include "Engine/GameTool/Utility/Vector/Vector3.h"
#include "Engine/GameTool/Utility/Vector/Vector2.h"
#include "../Component.h"
#include "Engine/GameTool/Utility/Maths.h"

struct Transform 
{
public:
	Transform(Vector3 pPosition = Vector3::Zero, Vector3 pScale = Vector3::One, float pRotation = 0.0f);

	Vector3 Right() const { return Vector3(Maths::Cos(mRotation), -Maths::Sin(mRotation), 0); }
	Vector3 Up() const { return Vector3(Maths::Sin(mRotation), -Maths::Cos(mRotation), 0); }
	//Vector3 Forward() const {return Vector3::Transform(Vector3::unitX, mRotation);}
	Vector3 Forward() const { return Vector3::Zero; }

	Vector3 mPosition = Vector3::Zero;
	Vector3 mScale = Vector3::One;
	float mRotation = 0.0f;
};

