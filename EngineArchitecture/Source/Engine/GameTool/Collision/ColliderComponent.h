#pragma once

#include "../Component.h"
#include "Engine/GameTool/Utility/Vector/Vector4.h"

class RendererSDL;

class ColliderComponent : public Component
{
public:
	void OnStart() override;
	void OnEnd() override;

	virtual bool Collision(const ColliderComponent* pComponent) = 0;
	virtual void DebugRender(RendererSDL* rRenderer) = 0;

	//Variables
	Color mColor{ 255,0,0,255 };
};

