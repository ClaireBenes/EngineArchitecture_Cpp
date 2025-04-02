#pragma once

#include "Engine/GameTool/Utility/Maths.h"
#include "Engine/GameTool/Utility/Vector/Vector3.h"

class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

	Quaternion()
	{
		*this = Quaternion::Identity;
	}

	// This directly sets the quaternion components --
	// don't use for axis/angle
	explicit Quaternion(float inX, float inY, float inZ, float inW);

	// Construct the quaternion from an axis and angle
	// It is assumed that axis is already normalized,
	// and the angle is in radians
	explicit Quaternion(const Vector3& axis, float angle);

	// Construct quaternion from a specific angle
	explicit Quaternion(float pitch, float yaw, float roll);

	void Set(float inX, float inY, float inZ, float inW);
	void Conjugate();
	void Normalize();

	float LengthSqr() const;
	float Length() const;

	float GetPitch() const;
	float GetYaw() const;
	float GetRoll() const;

	static float Dot(const Quaternion& a, const Quaternion& b);

	static Quaternion Normalize(const Quaternion& q);

	static Quaternion Lerp(const Quaternion& a, const Quaternion& b, float f);
	static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float f);
	static Quaternion Concatenate(const Quaternion& q, const Quaternion& p);

	static Quaternion LookAt(const Vector3& forward,const Vector3& up);
	static Quaternion LookAt(const Vector3& origin,const Vector3& target,const Vector3& up);

	Quaternion operator+(const Quaternion& p)
	{
		return Concatenate(*this, p);
	}

	class Matrix4 AsMatrix() const;
	static const Quaternion Identity;
};