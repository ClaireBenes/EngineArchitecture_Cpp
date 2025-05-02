#pragma once

#include "Engine/GameTool/Utility/Vector/Vector3.h"

/*
Represents an axis-aligned bounding box (AABB) in 3D space.
Used primarily for collision detection and spatial calculations.
 */
struct Box
{
	/*
	Minimum corner of the box in 3D space.
	Defaults to (-1, -1, -1).
	 */
	Vector3 min = Vector3::One * -1.0f;
	/*
	Maximum corner of the box in 3D space.
	Defaults to (1, 1, 1).
	 */
	Vector3 max = Vector3::One;

	/*
	 * Calculates the size (width, height, depth) of the box.
	 * @return A Vector3 representing the size of the box.
	 */
	Vector3 GetSize() const;
	/*
	 * Calculates the center point of the box.
	 * @return A Vector3 representing the center of the box.
	 */
	Vector3 GetCenter() const;

	/*
	 * Checks if two AABBs intersect (collide).
	 * @param a The first box.
	 * @param b The second box.
	 * @return True if the boxes intersect, false otherwise.
	 */
	static bool Collision(const Box& a, const Box& b);
};

