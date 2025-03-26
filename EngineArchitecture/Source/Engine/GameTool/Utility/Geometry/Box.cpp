#include "Box.h"

Vector3 Box::GetSize() const
{
	return max - min;
}

Vector3 Box::GetCenter() const
{
	return ( min + max ) * 0.5f;
}

bool Box::Collision(const Box& a, const Box& b)
{
	return (a.min.x < b.max.x) && (a.max.x > b.min.x)
		&& (a.min.y < b.max.y) && (a.max.y > b.min.y) 
		&& (a.min.z < b.max.z) && (a.max.z > b.min.z);
}
