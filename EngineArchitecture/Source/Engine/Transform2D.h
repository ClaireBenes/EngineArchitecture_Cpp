#pragma once

#include "Engine/Vector2.h"
#include "Engine/Component.h"

class Transform2D : public Component
{
public:
	Transform2D(Vector2 pPosition = Vector2::ZERO, Vector2 pScale = Vector2::ONE, float pRotation = 0.0f);

private:
	Vector2 mPosition = Vector2::ZERO;
	Vector2 mScale = Vector2::ONE;
	float mRotation = 0.0f;
};

