#include "Vector2.h"

const Vector2 Vector2::ZERO(0.0f, 0.0f);
const Vector2 Vector2::ONE(1.0f, 1.0f);

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Vector2::GetMagnitude() const
{
	return std::sqrt(x * x + y * y);
}

void Vector2::Normalize()
{
	float lenght = GetMagnitude();

	if(lenght == 0.0f)
	{
		return;
	}
	else
	{
		( *this ) /= GetMagnitude();
	}

}

Vector2 Vector2::Normalized()
{
	float lenght = GetMagnitude();

	if(lenght == 0.0f)
	{
		return ZERO;
	}
	else
	{
		return (*this) / lenght;
	}
}

float Vector2::Dot(const Vector2& left, const Vector2& right) const
{
	return left.x * right.x + left.y * right.y;
}

float Vector2::Cross(const Vector2& vector) const
{
	return x * vector.y - y * vector.x;
}

void Vector2::operator+=(const Vector2& vector)
{
	x += vector.x;
	y += vector.y;
}

void Vector2::operator-=(const Vector2& vector)
{
	x -= vector.x;
	y -= vector.y;
}

void Vector2::operator*=(const float value)
{
	x *= value;
	y *= value;
}

void Vector2::operator/=(const float value)
{
	x /= value;
	y /= value;
}


Vector2 operator+(const Vector2& left, const Vector2& right)
{
	return { left.x + right.x, right.x + right.y };
}

Vector2 operator-(const Vector2& left, const Vector2& right)
{
	return { left.x - right.x, right.x - right.y };
}

Vector2 operator*(const float value, const Vector2& vector)
{
	return { value * vector.x, value - vector.y };
}

Vector2 operator/(const float value, const Vector2& vector)
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

Vector2 operator/(const Vector2& vector, const float value)
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


