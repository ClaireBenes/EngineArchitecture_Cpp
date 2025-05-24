#pragma once

#include <iostream>
#include <cmath>
#include <string>

/**
 * @brief A class representing a 2D vector.
 *
 * It supports vector arithmetic,
 * geometric computations such as magnitude, normalization, dot and cross products,
 * and includes operator overloads for intuitive use.
 */
struct Vector2
{
	/**
	 * @brief Default constructor. Initializes vector to (0, 0).
	 */
	Vector2();
	/**
	 * @brief Initializes the vector with specified x and y values.
	 * @param x The x component.
	 * @param y The y component.
	 */
	Vector2(float x, float y);
	/**
	 * @brief Initializes both x and y with the same value.
	 * @param x The value to assign to both x and y.
	 */
	Vector2(float x);

	//Variables
	float x = 0;
	float y = 0;

	static const Vector2 ZERO, ONE;

	//Functions

	/**
	 * @brief Returns the magnitude (length) of the vector.
	 */
	float Magnitude() const;
	/**
	 * @brief Returns the squared length of the vector (avoids square root for performance).
	 */
	float SqrLength() const;

	/**
	 * @brief Normalizes the vector to unit length.
	 * If the vector is zero-length, it remains unchanged.
	 */
	void Normalize();
	/**
	 * @brief Returns a new unit-length vector in the same direction.
	 * If the original vector has zero length, returns Vector2::ZERO.
	 */
	Vector2 Normalized();

	/**
	 * @brief Computes the dot product of two vectors.
	 * @param left The first vector.
	 * @param right The second vector.
	 * @return A scalar representing how aligned the vectors are.
	 */
	float Dot(const Vector2& left, const Vector2& right) const;
	/**
	 * @brief Computes the 2D cross product between this and another vector.
	 * The result is a scalar equal to the Z-component of a 3D cross product.
	 * @param vector The other vector.
	 */
	float Cross(const Vector2& vector) const;

	/**
	 * @brief Converts the vector to a readable string format.
	 * @return String in format (x , y).
	 */
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

