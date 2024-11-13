#pragma once

#include <iostream>
#include <cmath>
#include <string>

#include "Vector3.h"

//alias
using Color = Vector4;

struct Vector4
{
	Vector4();
	Vector4(float x, float y, float z, float w);
	Vector4(Vector3 vec3, float w);

	//Variables
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 0;

	static const Vector4 ZERO, ONE;

	//functions
	std::string ToString() const;
};

