#pragma once

#include "Engine/GameTool/Component.h"
#include "Engine//GameTool/Vector/Vector4.h"

class Renderer;

class RenderComponent : public Component
{
public:
	//Variables
	virtual void Render(Renderer* rRenderer) = 0;
	Color mColor{ 255,255,255,255 };
};

