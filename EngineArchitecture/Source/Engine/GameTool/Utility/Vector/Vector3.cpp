#include "Vector3.h"

#include "Engine/GameTool/Utility/Maths.h"
#include "Engine/GameTool/Utility/Matrix/Matrix4.h"
#include "Engine/GameTool/Utility/Quaternion/Quaternion.h"

const Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::One(1.0f, 1.0f, 1.0f);

const Vector3 Vector3::Forward(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::Up(0.0f, -1.0f, 0.0f); // TODO: Check whether it should be negative or if it depends on the renderer type
const Vector3 Vector3::Right(1.0f, 0.0f, 0.0f);

const Vector3 Vector3::Backward(0.0f, 0.0f, -1.0f);
const Vector3 Vector3::Down(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::Left(-1.0f, 0.0f, 0.0f);

const Vector3 Vector3::Infinity(Maths::INFINITY_POS, Maths::INFINITY_POS, Maths::INFINITY_POS);
const Vector3 Vector3::MinusInfinity(Maths::INFINITY_NEG, Maths::INFINITY_NEG, Maths::INFINITY_NEG);

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float x)
{
	this->x = x;
	this->y = x;
	this->z = x;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(Vector2 vec2)
{
	x = vec2.x;
	y = vec2.y;
	z = 0;
}

float Vector3::Magnitude() const
{
	return std::sqrt(MagnitudeSqr());
}

float Vector3::MagnitudeSqr() const
{
	return ( x * x + y * y + z * z );
}

float Vector3::Magnitude2D() const
{
	return std::sqrt(Magnitude2DSqr());
}

float Vector3::Magnitude2DSqr() const
{
	return (x * x + z * z);
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
	Vector3 temp(x, y, z);
	temp.Normalize();
	return temp;
}

// Normalize the provided vector
Vector3 Vector3::Normalize(const Vector3& vec)
{
	Vector3 temp = vec;
	temp.Normalize();
	return temp;
}

void Vector3::Normalize2D()
{
	float lenght = Magnitude2D();

	if (lenght == 0.0f)
	{
		return;
	}
	else
	{
		x /= lenght;
		y = 0.0f;
		z /= lenght;
	}
}

Vector3 Vector3::Normalized2D()
{
	Vector3 temp(x, 0.0f, z);
	temp.Normalize2D();
	return temp;
}

// Dot product between two vectors (left dot right)
float Vector3::Dot(const Vector3& left, const Vector3& right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z;
}

float Vector3::Distance(Vector3& a, Vector3& b)
{
	return ( a - b ).Magnitude();
}

// Cross product between two vectors (this cross vector)
Vector3 Vector3::Cross(const Vector3& vector) const
{
	return { y * vector.z - z * vector.y, z * vector.x - x * vector.z, x * vector.y - y * vector.x};
}

// Cross product between two vectors (a cross b)
Vector3 Vector3::Cross(const Vector3& left, const Vector3& right)
{
	return { left.y * right.z - left.z * right.y, left.z * right.x - left.x * right.z, left.x * right.y - left.y * right.x };
}

// Lerp from A to B by f
Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float f)
{
	return Vector3(a + f * ( b - a ));
}

// Reflect V about (normalized) N
Vector3 Vector3::Reflect(const Vector3& v, const Vector3& n)
{
	return v - 2.0f * Vector3::Dot(v, n) * n;
}

std::string Vector3::ToString() const
{
	return "(" + std::to_string(x) + " , " + std::to_string(y) + " , " + std::to_string(z) + ")";
}

const float* Vector3::GetAsFloatPtr() const
{
	return reinterpret_cast< const float* >( &x );
}

Vector3 Vector3::Transform(Vector3& vec, Matrix4& mat4, float w)
{
	Vector3 retVal;
	
	retVal.x = vec.x * mat4.mat[0][0] + vec.y * mat4.mat[1][0] +
		vec.z * mat4.mat[2][0] + w * mat4.mat[3][0];
	retVal.y = vec.x * mat4.mat[0][1] + vec.y * mat4.mat[1][1] +
		vec.z * mat4.mat[2][1] + w * mat4.mat[3][1];
	retVal.z = vec.x * mat4.mat[0][2] + vec.y * mat4.mat[1][2] +
		vec.z * mat4.mat[2][2] + w * mat4.mat[3][2];
	//ignore w since we aren't returning a new value for it...
	return retVal;
}

// This will transform the vector and renormalize the w component
Vector3 Vector3::TransformWithPerspDiv(Vector3& vec, Matrix4& mat4, float w)
{
	Vector3 retVal;
	retVal.x = vec.x * mat4.mat[0][0] + vec.y * mat4.mat[1][0] +
		vec.z * mat4.mat[2][0] + w * mat4.mat[3][0];
	retVal.y = vec.x * mat4.mat[0][1] + vec.y * mat4.mat[1][1] +
		vec.z * mat4.mat[2][1] + w * mat4.mat[3][1];
	retVal.z = vec.x * mat4.mat[0][2] + vec.y * mat4.mat[1][2] +
		vec.z * mat4.mat[2][2] + w * mat4.mat[3][2];
	float transformedW = vec.x * mat4.mat[0][3] + vec.y * mat4.mat[1][3] +
		vec.z * mat4.mat[2][3] + w * mat4.mat[3][3];
	if(!Maths::NearZero(Maths::Abs(transformedW)))
	{
		transformedW = 1.0f / transformedW;
		retVal *= transformedW;
	}
	return retVal;
}

// Transform a Vector3 by a quaternion
Vector3 Vector3::Transform(const Vector3& v, const Quaternion& q)
{
	Vector3 qv(q.x, q.y, q.z);
	Vector3 retVal = v;
	retVal += 2.0f * Vector3::Cross(qv, Vector3::Cross(qv, v) + q.w * v);
	return retVal;
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

Vector3 Vector3::operator-() const
{
	return Vector3 { -x, -y, -z };
}

bool operator==(const Vector3& left, const Vector3& right)
{
	return left.x == right.x && left.y == right.y && left.z == right.z;
}

// +
Vector3 operator+(const Vector3& left, const Vector3& right)
{
	return { left.x + right.x, left.y + right.y, left.z + right.z };
}

// -
Vector3 operator-(const Vector3& left, const Vector3& right)
{
	return { left.x - right.x, left.y - right.y, left.z - right.z };
}

// *
Vector3 operator*(const Vector3& left, const Vector3& right)
{
	return { left.x * right.x, left.y * right.y, left.z * right.z };
}

// vector * float
Vector3 operator*(const Vector3& vector, const float value)
{
	return { value * vector.x, value * vector.y, value * vector.z };
}

// float * vector
Vector3 operator*(const float value, const Vector3& vector)
{
	return { value * vector.x, value * vector.y, value * vector.z };
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
