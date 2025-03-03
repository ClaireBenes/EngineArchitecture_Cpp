#include "Vector4.h"

#include "Engine/GameTool/Utility/Maths.h"

const Vector4 Vector4::ZERO(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::ONE(1.0f, 1.0f, 1.0f, 1.0f);

Vector4::Vector4()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4::Vector4(Vector3 vec3, float w)
{
	x = vec3.x;
	y = vec3.y;
	z = vec3.z;
	this->w = w;
}

float Vector4::Magnitude() const
{
	return ( Maths::Sqrt(MagnitudeSqr()));
}

float Vector4::MagnitudeSqr() const
{
	return ( x * x + y * y + z * z + w * w );
}

void Vector4::Normalize()
{
	float len = Magnitude();
	x /= len;
	y /= len;
	z /= len;
	w /= len;
}

// Normalize the provided vector
Vector4 Vector4::Normalize(const Vector4& vec)
{
	Vector4 temp = vec;
	temp.Normalize();
	return temp;
}

// Dot product between two vectors (a dot b)
float Vector4::Dot(const Vector4& a, const Vector4& b)
{
	return ( a.x * b.x + a.y * b.y + a.z * b.z );
}

// Cross product between two vectors (a cross b)
Vector4 Vector4::Cross(const Vector4& a, const Vector4& b)
{
	Vector4 temp;
	temp.x = a.y * b.z - a.z * b.y;
	temp.y = a.z * b.x - a.x * b.z;
	temp.z = a.x * b.y - a.y * b.x;
	return temp;
}

// Lerp from A to B by f
Vector4 Vector4::Lerp(const Vector4& a, const Vector4& b, float f)
{
	return Vector4(a + f * ( b - a ));
}

// Reflect V about (normalized) N
Vector4 Vector4::Reflect(const Vector4& v, const Vector4& n)
{
	return v - 2.0f * Vector4::Dot(v, n) * n;
}

std::string Vector4::ToString() const
{
	return "(" + std::to_string(x) + " , " + std::to_string(y) + " , " + std::to_string(z) + " , " + std::to_string(w) + ")";
}

// Cast to a const float pointer
const float* Vector4::GetAsFloatPtr() const
{
	return reinterpret_cast< const float* >( &x );
}

float& Vector4::operator[](int i)
{
	return *( reinterpret_cast< float* >( &x ) + i );
}

// Scalar *=
Vector4& Vector4::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
}

// Vector +=
Vector4& Vector4::operator+=(const Vector4& right)
{
	x += right.x;
	y += right.y;
	z += right.z;
	w += right.w;
	return *this;
}

// Vector -=
Vector4& Vector4::operator-=(const Vector4& right)
{
	x -= right.x;
	y -= right.y;
	z -= right.z;
	w -= right.w;
	return *this;
}

// Vector addition (a + b)
Vector4 operator+(const Vector4& a, const Vector4& b)
{
	return Vector4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

// Vector subtraction (a - b)
Vector4 operator-(const Vector4& a, const Vector4& b)
{
	return Vector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

// Component-wise multiplication
Vector4 operator*(const Vector4& left, const Vector4& right)
{
	return Vector4();
}

// Scalar multiplication
Vector4 operator*(const Vector4& vec, float scalar)
{
	return Vector4(vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar);
}

// Scalar multiplication
Vector4 operator*(float scalar, const Vector4& vec)
{
	return Vector4(vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar);
}
