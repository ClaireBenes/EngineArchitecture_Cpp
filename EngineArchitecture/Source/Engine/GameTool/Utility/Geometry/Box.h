#pragma once

#include "Engine/GameTool/Utility/Vector/Vector3.h"

struct Box
{
	Vector3 min = Vector3::One * -1.0f;
	Vector3 max = Vector3::One;

	Vector3 GetSize() const;
	Vector3 GetCenter() const;

	static bool Collision(const Box& a, const Box& b);
};

