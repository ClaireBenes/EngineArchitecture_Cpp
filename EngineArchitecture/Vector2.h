#pragma once

#include <iostream>
#include <cmath>

struct Vector2
{
	Vector2(float x, float y);

	//Variables
	float x = 0;
	float y = 0;

	static const Vector2 ZERO, ONE;

	//Functions
	float GetMagnitude() const;
	inline void Normalize();
	inline Vector2 Normalized();

	float Dot(const Vector2& left, const Vector2& right) const;
	float Cross(const Vector2& vector) const;

	inline void operator+=(const Vector2& vector);
	inline void operator-=(const Vector2& vector);
	inline void operator*=(const float value);
	inline void operator/=(const float value);
};

