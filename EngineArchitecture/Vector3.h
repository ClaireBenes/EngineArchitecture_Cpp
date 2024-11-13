#pragma once

#include <iostream>
#include <cmath>
#include <string>

class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);

	//Variables
	float x = 0;
	float y = 0;
	float z = 0;

	static const Vector3 ZERO, ONE;

	//functions
	std::string ToString() const;
};

