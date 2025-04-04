#pragma once

#include <iostream>
#include <cmath>
#include <string>

#include "Vector2.h"

class Matrix4;
class Quaternion;

class Vector3
{
public:
	Vector3();
	Vector3(float x);
	Vector3(float x, float y, float z);
	Vector3(Vector2 vec2);

	//Variables
	float x = 0;
	float y = 0;
	float z = 0;

	static const Vector3 Zero, One, Forward, Up, Right, Backward, Down, Left, Infinity, MinusInfinity ;

	//Functions
	float Magnitude() const;
	float MagnitudeSqr() const;

	float Magnitude2D() const;
	float Magnitude2DSqr() const;

	void Normalize();
	Vector3 Normalized();
	static Vector3 Normalize(const Vector3& vec);

	void Normalize2D();
	Vector3 Normalized2D();

	static float Dot(const Vector3& left, const Vector3& right);
	static float Distance(Vector3& a, Vector3& b);
	static Vector3 Cross(const Vector3& left, const Vector3& right);
	Vector3 Cross(const Vector3& vector) const;

	static Vector3 Lerp(const Vector3& a, const Vector3& b, float f);
	static Vector3 Reflect(const Vector3& v, const Vector3& n);

	std::string ToString() const;
	const float* GetAsFloatPtr() const;

	static Vector3 Transform(Vector3& vec, class Matrix4& mat4, float w = 1.0f);
	static Vector3 TransformWithPerspDiv(Vector3& vec, class Matrix4& mat4, float w = 1.0f);
	static Vector3 Transform(const Vector3& v, const class Quaternion& q);

	//Operator
	Vector3 operator-() const;

	void operator+=(const Vector3& vector);
	void operator-=(const Vector3& vector);
	void operator*=(const float value);
	void operator/=(const float value);

	friend bool operator==(const Vector3& left, const Vector3& right);

	friend Vector3 operator+(const Vector3& left, const Vector3& right);
	friend Vector3 operator-(const Vector3& left, const Vector3& right);
	friend Vector3 operator/(const Vector3& vector, const float value);
	friend Vector3 operator*(const Vector3& left, const Vector3& right);
	friend Vector3 operator*(const Vector3& vector, const float value);
	friend Vector3 operator*(const float value, const Vector3& vector);
};

