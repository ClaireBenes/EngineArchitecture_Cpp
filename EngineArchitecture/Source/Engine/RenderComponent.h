#pragma once

#include "Component.h"
#include "Vector4.h"

class Renderer;

class RenderComponent : public Component
{
public:
	virtual void Render(Renderer* rRenderer) = 0;
	Color mColor{ 255,255,255,255 };
};

