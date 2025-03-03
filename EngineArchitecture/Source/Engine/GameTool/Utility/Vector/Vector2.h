#pragma once

#include <iostream>
#include <cmath>
#include <string>

struct Vector2
{
	Vector2();
	Vector2(float x, float y);
	Vector2(float x);

	//Variables
	float x = 0;
	float y = 0;

	static const Vector2 ZERO, ONE;

	//Functions
	float Magnitude() const;
	float SqrLength() const;
	void Normalize();
	Vector2 Normalized();

	float Dot(const Vector2& left, const Vector2& right) const;
	float Cross(const Vector2& vector) const;

	std::string ToString() const;

	//Operator
	void operator+=(const Vector2& vector);
	void operator-=(const Vector2& vector);
	void operator*=(const float value);
	void operator/=(const float value);

	friend bool operator==(const Vector2& left, const Vector2& right);

	friend Vector2 operator+(const Vector2& left, const Vector2& right);
	friend Vector2 operator-(const Vector2& left, const Vector2& right);
	friend Vector2 operator*(const float value, const Vector2& vector);
	friend Vector2 operator*(const Vector2& vector, const float value);
	friend Vector2 operator/(const Vector2& vector, const float value);
};

