#pragma once

#include "Engine/GameTool/Component.h"
#include "Engine/GameTool/Utility/Vector/Vector4.h"

class IRenderer;

class RenderComponent : public Component
{
public:
	//Variables
	virtual void Render(IRenderer* rRenderer) = 0;
	Color mColor{ 255,255,255,255 };
};

