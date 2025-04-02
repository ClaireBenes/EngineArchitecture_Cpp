#include "Quaternion.h"

#include "Engine/GameTool/Utility/Vector/Vector4.h"
#include "Engine/GameTool/Utility/Matrix/Matrix4.h"
#include "Engine/GameTool/Utility/Matrix/Matrix4.h"

#include <array>

using std::array;

const Quaternion Quaternion::Identity(0.0f, 0.0f, 0.0f, 1.0f);

Quaternion::Quaternion(float xP, float yP, float zP, float wP)
{
	Set(xP, yP, zP, wP);
}

Quaternion::Quaternion(const Vector3& axis, float angle)
{
	float scalar = Maths::Sin(angle / 2.0f);
	x = axis.x * scalar;
	y = axis.y * scalar;
	z = axis.z * scalar;
	w = Maths::Cos(angle / 2.0f);
}

void Quaternion::Set(float inX, float inY, float inZ, float inW)
{
	x = inX;
	y = inY;
	z = inZ;
	w = inW;
}

void Quaternion::Conjugate()
{
	x *= -1.0f;
	y *= -1.0f;
	z *= -1.0f;
}

void Quaternion::Normalize()
{
	float len = Length();
	x /= len;
	y /= len;
	z /= len;
	w /= len;
}

float Quaternion::LengthSqr() const
{
	return (x * x + y * y + z * z + w * w);
}

float Quaternion::Length() const
{
	return Maths::Sqrt(LengthSqr());
}

float Quaternion::GetPitch() const
{
	return Maths::ATan2(
		2.0f * (w * x + y * z),
		1.0f - 2.0f * (x * x + y * y));
}

float Quaternion::GetYaw() const
{
	double sinp = 2 * (w * y - z * x);
	if (std::abs(sinp) >= 1)
		return std::copysign(Maths::PI_HALVED, sinp); // use 90 degrees if out of range
	else
		return std::asin(sinp);
}

float Quaternion::GetRoll() const
{
	return Maths::ATan2(
		2.0f * (w * z + x * y),
		1.0f - 2.0f * (y * y + z * z));
}

// Normalize the provided quaternion
Quaternion Quaternion::Normalize(const Quaternion& q)
{
	Quaternion retVal = q;
	retVal.Normalize();
	return retVal;
}

// Linear interpolation
Quaternion Quaternion::Lerp(const Quaternion& a, const Quaternion& b, float f)
{
	Quaternion retVal;
	retVal.x = Maths::Lerp(a.x, b.x, f);
	retVal.y = Maths::Lerp(a.y, b.y, f);
	retVal.z = Maths::Lerp(a.z, b.z, f);
	retVal.w = Maths::Lerp(a.w, b.w, f);
	retVal.Normalize();
	return retVal;
}

float Quaternion::Dot(const Quaternion& a, const Quaternion& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

// Spherical Linear Interpolation
Quaternion Quaternion::Slerp(const Quaternion& a, const Quaternion& b, float f)
{
	float rawCosm = Quaternion::Dot(a, b);

	float cosom = -rawCosm;
	if (rawCosm >= 0.0f)
	{
		cosom = rawCosm;
	}

	float scale0, scale1;

	if (cosom < 0.9999f)
	{
		const float omega = Maths::ACos(cosom);
		const float invSin = 1.f / Maths::Sin(omega);
		scale0 = Maths::Sin((1.f - f) * omega) * invSin;
		scale1 = Maths::Sin(f * omega) * invSin;
	}
	else
	{
		// Use linear interpolation if the quaternions
		// are collinear
		scale0 = 1.0f - f;
		scale1 = f;
	}

	if (rawCosm < 0.0f)
	{
		scale1 = -scale1;
	}

	Quaternion retVal;
	retVal.x = scale0 * a.x + scale1 * b.x;
	retVal.y = scale0 * a.y + scale1 * b.y;
	retVal.z = scale0 * a.z + scale1 * b.z;
	retVal.w = scale0 * a.w + scale1 * b.w;
	retVal.Normalize();
	return retVal;
}

// Concatenate
// Rotate by q FOLLOWED BY p
Quaternion Quaternion::Concatenate(const Quaternion& q, const Quaternion& p)
{
	Quaternion retVal;

	// Vector component is:
	// ps * qv + qs * pv + pv x qv
	Vector3 qv(q.x, q.y, q.z);
	Vector3 pv(p.x, p.y, p.z);
	Vector3 newVec = p.w * qv + q.w * pv + Vector3::Cross(pv, qv);
	retVal.x = newVec.x;
	retVal.y = newVec.y;
	retVal.z = newVec.z;

	// Scalar component is:
	// ps * qs - pv . qv
	retVal.w = p.w * q.w - Vector3::Dot(pv, qv);

	return retVal;
}

Matrix4 Quaternion::AsMatrix() const
{
	Matrix4 m;

	const float xx = x * x;
	const float yy = y * y;
	const float zz = z * z;
	const float ww = w * w;
	const float xy = x * y;
	const float xz = x * z;
	const float xw = x * w;
	const float yz = y * z;
	const float yw = y * w;
	const float zw = z * w;

	m.mat[0][0] = 1.0f - 2.0f * (yy + zz);
	m.mat[0][1] =        2.0f * (xy - zw);
	m.mat[0][2] =        2.0f * (xz + yw);
	m.mat[0][3] =        0.0f;

	m.mat[1][0] =        2.0f * (xy + zw);
	m.mat[1][1] = 1.0f - 2.0f * (xx + zz);
	m.mat[1][2] =        2.0f * (yz - xw);
	m.mat[1][3] =        0.0f;

	m.mat[2][0] =        2.0f * (xz - yw);
	m.mat[2][1] =        2.0f * (yz + xw);
	m.mat[2][2] = 1.0f - 2.0f * (xx + yy);
	m.mat[2][3] =        0.0f;

	m.mat[3][0] =        0.0f;
	m.mat[3][1] =        0.0f;
	m.mat[3][2] =        0.0f;
	m.mat[3][3] =        1.0f;

	return m;
}
