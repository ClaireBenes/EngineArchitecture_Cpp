#include "Vector2.h"

const Vector2 Vector2::ZERO(0.0f, 0.0f);
const Vector2 Vector2::ONE(1.0f, 1.0f);

//Constructors
Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::Vector2(float x)
{
	this->x = x;
	this->y = x;
}

//Magnitude
float Vector2::Magnitude() const
{
	return std::sqrt(x * x + y * y);
}

float Vector2::SqrLength() const
{
	return (x * x + y * y);
}

//Normalize
void Vector2::Normalize()
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

//Normalized
Vector2 Vector2::Normalized()
{
	float lenght = Magnitude();

	if(lenght == 0.0f)
	{
		return ZERO;
	}
	else
	{
		return (*this) / lenght;
	}
}

//Dot
float Vector2::Dot(const Vector2& left, const Vector2& right) const
{
	return left.x * right.x + left.y * right.y;
}

//Cross
float Vector2::Cross(const Vector2& vector) const
{
	return x * vector.y - y * vector.x;
}

//return Vector2 in string
std::string Vector2::ToString() const
{
	return "(" + std::to_string(x) + " , " + std::to_string(y) + ")";
}

// +=
void Vector2::operator+=(const Vector2& vector)
{
	x += vector.x;
	y += vector.y;
}

// -=
void Vector2::operator-=(const Vector2& vector)
{
	x -= vector.x;
	y -= vector.y;
}

// *=
void Vector2::operator*=(const float value)
{
	x *= value;
	y *= value;
}

// /=
void Vector2::operator/=(const float value)
{
	x /= value;
	y /= value;
}

// +
Vector2 operator+(const Vector2& left, const Vector2& right)
{
	return { left.x + right.x, right.y + left.y };
}

// -
Vector2 operator-(const Vector2& left, const Vector2& right)
{
	return { left.x - right.x, left.y - right.y };
}

// *
Vector2 operator*(const float value, const Vector2& vector)
{
	return { value * vector.x, value * vector.y };
}

Vector2 operator*(const Vector2& vector, const float value)
{
	return { value * vector.x, value * vector.y };
}

// divide in one order 
Vector2 operator/(const float value, const Vector2& vector)
{
	if(vector.x != 0 && vector.y != 0)
	{
		return { value / vector.x, value / vector.y };
	}
	else
	{
		throw std::invalid_argument("Cannot divide by 0.");
	}
}

// divide in different order
Vector2 operator/(const Vector2& vector, const float value)
{
	if(value != 0)
	{
		return { vector.x / value, vector.y / value };
	}
	else
	{
		throw std::invalid_argument("Cannot divide by 0.");
	}
}


