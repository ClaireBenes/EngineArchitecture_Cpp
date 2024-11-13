#include "Vector4.h"

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

std::string Vector4::ToString() const
{
	return "(" + std::to_string(x) + " , " + std::to_string(y) + " , " + std::to_string(z) + " , " + std::to_string(w) + ")";
}

