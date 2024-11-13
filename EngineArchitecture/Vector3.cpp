#include "Vector3.h"

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

std::string Vector3::ToString() const
{
	return "(" + std::to_string(x) + " , " + std::to_string(y) + " , " + std::to_string(z) + ")";
}
