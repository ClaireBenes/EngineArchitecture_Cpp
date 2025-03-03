#pragma once

#include "Engine/GameTool/Utility/Vector/Vector2.h"
#include "../Component.h"
#include "Engine/GameTool/Utility/Math.h"

struct Transform2D 
{
public:
	Transform2D(Vector2 pPosition = Vector2::ZERO, Vector2 pScale = Vector2::ONE, float pRotation = 0.0f);

	Vector2 Right() const { return Vector2(Maths::Cos(mRotation), -Maths::Sin(mRotation)); }
	Vector2 Up() const { return Vector2(Maths::Sin(mRotation), -Maths::Cos(mRotation)); }

	Vector2 mPosition = Vector2::ZERO;
	Vector2 mScale = Vector2::ONE;
	float mRotation = 0.0f;
};

