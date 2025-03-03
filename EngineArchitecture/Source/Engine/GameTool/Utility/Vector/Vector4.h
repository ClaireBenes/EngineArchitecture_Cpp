#pragma once

#include <iostream>
#include <cmath>
#include <string>

#include "Vector3.h"

struct Vector4
{
	friend class Matrix4;

public:
	Vector4();
	Vector4(float x, float y, float z, float w);
	Vector4(Vector3 vec3, float w = 0);

	//Variables
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 0;

	static const Vector4 ZERO, ONE;

	//functions
	float Magnitude() const;
	float MagnitudeSqr() const;

	void Normalize();
	static Vector4 Normalize(const Vector4& vec);

	static float Dot(const Vector4& a, const Vector4& b);
	static Vector4 Cross(const Vector4& a, const Vector4& b);
	static Vector4 Lerp(const Vector4& a, const Vector4& b, float f);
	static Vector4 Reflect(const Vector4& v, const Vector4& n);

	std::string ToString() const;
	const float* GetAsFloatPtr() const;

	float& operator[](int i);
	friend Vector4 operator+(const Vector4& a, const Vector4& b);
	friend Vector4 operator-(const Vector4& a, const Vector4& b);
	friend Vector4 operator*(const Vector4& left, const Vector4& right);
	friend Vector4 operator*(const Vector4& vec, float scalar);
	friend Vector4 operator*(float scalar, const Vector4& vec);
	Vector4& operator*=(float scalar);
	Vector4& operator+=(const Vector4& right);
	Vector4& operator-=(const Vector4& right);
};

//alias
using Color = Vector4;

