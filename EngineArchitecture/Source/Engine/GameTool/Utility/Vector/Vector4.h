#pragma once

#include <iostream>
#include <cmath>
#include <string>

#include "Vector3.h"

/*
Vector4 is a 4D vector class used in graphics, math, and color representations.
It supports arithmetic, normalization, dot/cross products, and interpolation.
 */
struct Vector4
{
	friend class Matrix4;

public:
	/*
	 Default constructor. Initializes components to zero.
	 */
	Vector4();
	/*
	 * Constructor with individual components.
	 * @param x X component.
	 * @param y Y component.
	 * @param z Z component.
	 * @param w W component.
	 */
	Vector4(float x, float y, float z, float w);
	/*
	 * Constructs a Vector4 from a Vector3 and a w component.
	 * @param vec3 The 3D vector to use for x, y, z.
	 * @param w The w component (default: 0.0f).
	 */
	Vector4(Vector3 vec3, float w = 0);

	//Variables
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 0;

	static const Vector4 ZERO, ONE;

	/*
	 * Computes the magnitude (length) of the vector.
	 * @return Magnitude of the vector.
	 */
	float Magnitude() const;
	/*
	 * Computes the squared magnitude of the vector.
	 * @return Squared magnitude.
	 */
	float MagnitudeSqr() const;

	/*
	 Normalizes the vector to unit length.
	 */
	void Normalize();
	/*
	 * Returns a normalized copy of the input vector.
	 * @param vec Vector to normalize.
	 * @return Normalized vector.
	 */
	static Vector4 Normalize(const Vector4& vec);

	/*
	 * Computes the dot product between two vectors.
	 * @param a First vector.
	 * @param b Second vector.
	 * @return Dot product result.
	 */
	static float Dot(const Vector4& a, const Vector4& b);
	/*
	 * Computes the 3D cross product of two vectors (ignores w).
	 * @param a First vector.
	 * @param b Second vector.
	 * @return Resulting vector from cross product (w = 0).
	 */
	static Vector4 Cross(const Vector4& a, const Vector4& b);

	/*
	 * Linearly interpolates between two vectors.
	 * @param a Start vector.
	 * @param b End vector.
	 * @param f Interpolation factor (0.0 to 1.0).
	 * @return Interpolated vector.
	 */
	static Vector4 Lerp(const Vector4& a, const Vector4& b, float f);
	/*
	 * Reflects a vector across a normal vector.
	 * @param v Incoming vector.
	 * @param n Normal vector (should be normalized).
	 * @return Reflected vector.
	 */
	static Vector4 Reflect(const Vector4& v, const Vector4& n);

	/*
	 * Converts the vector to a readable string format.
	 * @return String in format (x , y , z , w).
	 */
	std::string ToString() const;
	/*
	 * Gets a float pointer to the vector's data.
	 * @return Pointer to the first component (x).
	 */
	const float* GetAsFloatPtr() const;

	/*
	 * Accesses a component by index (0 = x, 1 = y, 2 = z, 3 = w).
	 * @param i Index of the component.
	 * @return Reference to the component.
	 */
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

