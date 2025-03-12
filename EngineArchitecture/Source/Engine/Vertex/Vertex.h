#pragma once

#include "Engine/GameTool/Utility/Vector/Vector3.h"
#include "Engine/GameTool/Utility/Vector/Vector2.h"

struct Vertex
{
	Vector3 position = Vector3::Zero;
	Vector3 normal = Vector3::Zero;
	Vector2 uv = Vector2::ONE;
};
