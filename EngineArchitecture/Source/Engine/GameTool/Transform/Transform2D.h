#pragma once

#include "../Vector/Vector2.h"
#include "../Component.h"

struct Transform2D 
{
public:
	Transform2D(Vector2 pPosition = Vector2::ZERO, Vector2 pScale = Vector2::ONE, float pRotation = 0.0f);

	Vector2 mPosition = Vector2::ZERO;
	Vector2 mScale = Vector2::ONE;
	float mRotation = 0.0f;
};

