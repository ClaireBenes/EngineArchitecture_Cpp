#pragma once

#include "../Component.h"
#include "../Vector/Vector4.h"

class Renderer;

class ColliderComponent : public Component
{
public:
	//Variables
	virtual void Render(Renderer* rRenderer) = 0;
	Color mColor{ 255,0,0,255 };
};

