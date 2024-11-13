#pragma once

#include <iostream>
#include <cmath>
#include <string>

#include "Vector2.h"

class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(Vector2 vec2, float z = 0);

	//Variables
	float x = 0;
	float y = 0;
	float z = 0;

	static const Vector3 ZERO, ONE, FORWARD, UP, RIGHT;

	//Functions
	float Magnitude() const;
	void Normalize();
	Vector3 Normalized();

	float Dot(const Vector3& left, const Vector3& right) const;
	float Distance(Vector3& a, Vector3& b);
	Vector3 Cross(const Vector3& vector) const;

	std::string ToString() const;

	//Operator
	void operator+=(const Vector3& vector);
	void operator-=(const Vector3& vector);
	void operator*=(const float value);
	void operator/=(const float value);

	friend Vector3 operator+(const Vector3& left, const Vector3& right);
	friend Vector3 operator-(const Vector3& left, const Vector3& right);
	friend Vector3 operator*(const float value, const Vector3& vector);
	friend Vector3 operator/(const Vector3& vector, const float value);
};

