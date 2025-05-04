#pragma once

#include "Engine/GameTool/Utility/Maths.h"
#include "Engine/GameTool/Utility/Vector/Vector3.h"

/*
Quaternion represents a rotation in 3D space using four components (x, y, z, w).
It supports construction from axis-angle, Euler angles, or component values,
and provides utility functions for normalization, interpolation, and conversion to matrices.
 */
class Quaternion
{
public:
	// Components of the quaternion
	float x;
	float y;
	float z;
	float w;

	/*
	Default constructor initializes the quaternion to the identity quaternion.
	The identity quaternion represents no rotation and is defined as (0, 0, 0, 1).
	 */
	Quaternion()
	{
		*this = Quaternion::Identity;
	}

	/*
	 * Constructs a quaternion using four float values representing the components (x, y, z, w).
	 * @param inX The x component of the quaternion's vector part.
	 * @param inY The y component of the quaternion's vector part.
	 * @param inZ The z component of the quaternion's vector part.
	 * @param inW The scalar component of the quaternion.
	 */
	explicit Quaternion(float inX, float inY, float inZ, float inW);

	/*
	 * Constructs a quaternion from an axis of rotation and an angle in radians.
	 * The axis is assumed to be normalized.
	 * @param axis The normalized axis of rotation.
	 * @param angle The rotation angle in radians.
	 */
	explicit Quaternion(const Vector3& axis, float angle);

	/*
	 * Constructs a quaternion from pitch, yaw, and roll (Euler angles).
	 * The pitch is rotation about the X-axis, yaw about the Y-axis, and roll about the Z-axis.
	 * @param pitch The rotation angle around the X-axis in radians.
	 * @param yaw The rotation angle around the Y-axis in radians.
	 * @param roll The rotation angle around the Z-axis in radians.
	 */
	explicit Quaternion(float pitch, float yaw, float roll);

	/*
	 * Sets the quaternion components explicitly. This method is intended for direct initialization,
	 * not for converting axis/angle or Euler angles.
	 * @param inX The x component of the quaternion.
	 * @param inY The y component of the quaternion.
	 * @param inZ The z component of the quaternion.
	 * @param inW The scalar component of the quaternion.
	 */
	void Set(float inX, float inY, float inZ, float inW);
	/*
	Conjugates the quaternion, flipping the sign of the vector part (x, y, z).
	 */
	void Conjugate();
	/*
	Normalizes the quaternion, ensuring it has a unit length (i.e., it represents a valid rotation).
	This method alters the current quaternion.
	 */
	void Normalize();

	/*
	 * Computes and returns the squared length of the quaternion.
	 * The squared length is the sum of the squares of the quaternion components.
	 * @return The squared length of the quaternion.
	 */
	float LengthSqr() const;
	/*
	 * Computes and returns the length (magnitude) of the quaternion.
	 * This is the square root of the squared length.
	 * @return The length of the quaternion.
	 */
	float Length() const;

	/*
	 * Computes the pitch (rotation around the X-axis) of the quaternion.
	 * @return The pitch angle in radians.
	 */
	float GetPitch() const;
	/*
	 * Computes the yaw (rotation around the Y-axis) of the quaternion.
	 * @return The yaw angle in radians.
	 */
	float GetYaw() const;
	/*
	 * Computes the roll (rotation around the Z-axis) of the quaternion.
	 * @return The roll angle in radians.
	 */
	float GetRoll() const;

	/*
	 * Computes the dot product between two quaternions.
	 * @param a The first quaternion.
	 * @param b The second quaternion.
	 * @return The dot product between quaternions a and b.
	 */
	static float Dot(const Quaternion& a, const Quaternion& b);
	/*
	 * Returns a normalized version of the given quaternion.
	 * Normalization scales the quaternion so that its length is 1.
	 * @param q The quaternion to normalize.
	 * @return A new quaternion that is the normalized version of q.
	 */
	static Quaternion Normalize(const Quaternion& q);

	/*
	 * Performs linear interpolation (Lerp) between two quaternions.
	 * @param a The starting quaternion.
	 * @param b The ending quaternion.
	 * @param f The interpolation factor (from 0 to 1).
	 * @return The interpolated quaternion.
	 */
	static Quaternion Lerp(const Quaternion& a, const Quaternion& b, float f);
	/*
	 * Performs spherical linear interpolation (Slerp) between two quaternions.
	 * @param a The starting quaternion.
	 * @param b The ending quaternion.
	 * @param f The interpolation factor (from 0 to 1).
	 * @return The interpolated quaternion.
	 */
	static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float f);
	/*
	 * Concatenates two quaternions (i.e., applies one rotation after the other).
	 * This is equivalent to multiplying the two quaternions.
	 * @param q The first quaternion (rotation to apply first).
	 * @param p The second quaternion (rotation to apply after q).
	 * @return A new quaternion that represents the combined rotation.
	 */
	static Quaternion Concatenate(const Quaternion& q, const Quaternion& p);

	/*
	 * Creates a quaternion representing the rotation to "look at" a target point.
	 * The resulting quaternion aligns the forward vector with the target direction,
	 * with the given up vector providing the direction of the "up" axis.
	 * @param forward The forward vector to align the quaternion to.
	 * @param up The up vector, typically (0, 1, 0).
	 * @return A quaternion that rotates an object to face the target direction.
	 */
	static Quaternion LookAt(const Vector3& forward,const Vector3& up);
	/*
	 * Creates a quaternion representing the rotation to "look at" a target point from an origin.
	 * This is equivalent to creating a "look at" rotation from the origin to the target, with the up vector.
	 * @param origin The starting point (usually the camera or object position).
	 * @param target The point to look at (the target position).
	 * @param up The up vector (usually (0, 1, 0)).
	 * @return A quaternion representing the look-at rotation.
	 */
	static Quaternion LookAt(const Vector3& origin,const Vector3& target,const Vector3& up);

	Quaternion operator+(const Quaternion& p)
	{
		return Concatenate(*this, p);
	}

	/**
	 * Converts the quaternion to a 4x4 matrix representation.
	 * The resulting matrix can be used for transforming 3D vectors by the quaternion's rotation.
	 * @return A Matrix4 object representing the quaternion as a rotation matrix.
	 */
	class Matrix4 AsMatrix() const;

	static const Quaternion Identity; // Identity quaternion: represents no rotation (used as a reference for default state).
};