#pragma once

#include <iostream>
#include <cmath>
#include <string>

#include "Vector2.h"

class Matrix4;
class Quaternion;

/**
 * @brief Vector3 is a 3D vector utility class used for position, direction, and math operations in 3D space.
 */
class Vector3
{
public:

	/**
	 * @brief Default constructor, initializes to (0,0,0). 
	 */
	Vector3();
	/**
	 * @brief Initializes all components to the same scalar value.
	 * @param x Scalar value to assign to x, y, and z.
	 */
	Vector3(float x);
	/**
	 * @brief Initializes vector with individual float components.
	 * @param x X component.
	 * @param y Y component.
	 * @param z Z component.
	 */
	Vector3(float x, float y, float z);
	/**
	 * @brief Constructs a Vector3 from a Vector2, setting z to 0.
	 * @param vec2 2D vector to use for x and y.
	 */
	Vector3(Vector2 vec2);

	//Variables
	float x = 0;
	float y = 0;
	float z = 0;

	static const Vector3 Zero, One, Forward, Up, Right, Backward, Down, Left, Infinity, MinusInfinity ;

	//Functions

	/**
	 * @brief Computes the magnitude (length) of the vector.
	 * @return Length of the vector.
	 */
	float Magnitude() const;
	/**
	 * @brief Computes the squared magnitude.
	 * @return Squared length of the vector.
	 */
	float MagnitudeSqr() const;

	/**
	 * @brief Computes 2D magnitude using x and z components only.
	 * @return Length in the XZ plane.
	 */
	float Magnitude2D() const;
	/**
	 * @brief Computes squared 2D magnitude using x and z components.
	 * @return Squared length in the XZ plane.
	 */
	float Magnitude2DSqr() const;

	/**
	 * @brief Normalizes the vector to unit length.
	 */
	void Normalize();
	/**
	 * @brief Returns a normalized copy of the vector.
	 * @return Unit-length vector in same direction.
	 */
	Vector3 Normalized();
	/**
	 * @brief Static method to normalize a vector.
	 * @param vec Vector to normalize.
	 * @return Normalized vector.
	 */
	static Vector3 Normalize(const Vector3& vec);

	/**
	 * @brief Normalizes x and z components to unit length (2D).
	 */
	void Normalize2D();

	/**
	 * @brief Returns a copy normalized in the XZ plane.
	 * @return 2D-normalized vector (y = 0).
	 */
	Vector3 Normalized2D();

	/**
	 * @brief Computes the dot product between two vectors.
	 * @param left First vector.
	 * @param right Second vector.
	 * @return Dot product result.
	 */
	static float Dot(const Vector3& left, const Vector3& right);
	/**
	 * @brief Computes the distance between two vectors.
	 * @param a First point.
	 * @param b Second point.
	 * @return Euclidean distance between a and b.
	 */
	static float Distance(Vector3& a, Vector3& b);
	/**
	 * @brief Computes the cross product with another vector.
	 * @param vector Other vector.
	 * @return Result of the cross product.
	 */
	static Vector3 Cross(const Vector3& left, const Vector3& right);
	/**
	 * @brief Computes the cross product between two vectors.
	 * @param left First vector.
	 * @param right Second vector.
	 * @return Cross product result.
	 */
	Vector3 Cross(const Vector3& vector) const;

	/**
	 * @brief Linearly interpolates between two vectors.
	 * @param a Starting vector.
	 * @param b Ending vector.
	 * @param f Interpolation factor (0.0 to 1.0).
	 * @return Interpolated vector.
	 */
	static Vector3 Lerp(const Vector3& a, const Vector3& b, float f);
	/**
	 * @brief Reflects a vector across a normal.
	 * @param v Incoming vector.
	 * @param n Normal vector (should be normalized).
	 * @return Reflected vector.
	 */
	static Vector3 Reflect(const Vector3& v, const Vector3& n);

	/**
	 * @brief Converts the vector to a string representation.
	 * @return String in format (x , y , z).
	 */
	std::string ToString() const;
	/**
	 * @brief Gets a pointer to the vector's float data.
	 * @return Pointer to x (useful for OpenGL).
	 */
	const float* GetAsFloatPtr() const;

	/**
	 * @brief Transforms the vector by a 4x4 matrix (ignores perspective divide).
	 * @param vec Vector to transform.
	 * @param mat4 Matrix to use.
	 * @param w Homogeneous coordinate (default: 1.0f).
	 * @return Transformed vector.
	 */
	static Vector3 Transform(Vector3& vec, class Matrix4& mat4, float w = 1.0f);
	/**
	 * @brief Transforms the vector by a matrix and applies perspective divide.
	 * @param vec Vector to transform.
	 * @param mat4 Matrix to use.
	 * @param w Homogeneous coordinate (default: 1.0f).
	 * @return Transformed and perspective-divided vector.
	 */
	static Vector3 TransformWithPerspDiv(Vector3& vec, class Matrix4& mat4, float w = 1.0f);
	/**
	 * @brief Transforms the vector by a quaternion rotation.
	 * @param v Vector to rotate.
	 * @param q Quaternion to apply.
	 * @return Rotated vector.
	 */
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

