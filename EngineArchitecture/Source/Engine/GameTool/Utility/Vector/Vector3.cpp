#include "Vector3.h"

const Vector3 Vector3::ZERO(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::ONE(1.0f, 1.0f, 1.0f);

const Vector3 Vector3::FORWARD(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::UP(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::RIGHT(1.0f, 0.0f, 0.0f);

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(Vector2 vec2, float z)
{
	x = vec2.x;
	y = vec2.y;
	this->z = z;
}

float Vector3::Magnitude() const
{
	return std::sqrt(x * x + y * y + z * z);
}

void Vector3::Normalize()
{
	float lenght = Magnitude();

	if(lenght == 0.0f)
	{
		return;
	}
	else
	{
		( *this ) /= Magnitude();
	}
}

Vector3 Vector3::Normalized()
{
	float lenght = Magnitude();

	if(lenght == 0.0f)
	{
		return ZERO;
	}
	else
	{
		return ( *this ) / lenght;
	}
}

float Vector3::Dot(const Vector3& left, const Vector3& right) const
{
	return left.x * right.x + left.y * right.y + left.z * right.z;
}

float Vector3::Distance(Vector3& a, Vector3& b)
{
	return ( a - b ).Magnitude();
}

Vector3 Vector3::Cross(const Vector3& vector) const
{
	return { y * vector.z - z * vector.y, z * vector.x - x * vector.z, x * vector.y - y * vector.x};
}

std::string Vector3::ToString() const
{
	return "(" + std::to_string(x) + " , " + std::to_string(y) + " , " + std::to_string(z) + ")";
}

// +=
void Vector3::operator+=(const Vector3& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
}

// -=
void Vector3::operator-=(const Vector3& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
}

// *=
void Vector3::operator*=(const float value)
{
	x *= value;
	y *= value;
	z *= value;
}

// /=
void Vector3::operator/=(const float value)
{
	x /= value;
	y /= value;
	z /= value;
}

// +
Vector3 operator+(const Vector3& left, const Vector3& right)
{
	return { left.x + right.x, right.x + right.y, left.z + right.z };
}

// -
Vector3 operator-(const Vector3& left, const Vector3& right)
{
	return { left.x - right.x, right.x - right.y, left.z - right.z };
}

// *
Vector3 operator*(const float value, const Vector3& vector)
{
	return { value * vector.x, value - vector.y, value * vector.z };
}

// divide in one order 
Vector3 operator/(const float value, const Vector3& vector)
{
	if(vector.x != 0 && vector.y != 0 && vector.z != 0)
	{
		return { value / vector.x, value / vector.y, value / vector.z };
	}
	else
	{
		throw std::invalid_argument("Cannot divide by 0.");
	}
}

// divide in different order
Vector3 operator/(const Vector3& vector, const float value)
{
	if(value != 0)
	{
		return { vector.x / value, vector.y / value, vector.z / value };
	}
	else
	{
		throw std::invalid_argument("Cannot divide by 0.");
	}
}
