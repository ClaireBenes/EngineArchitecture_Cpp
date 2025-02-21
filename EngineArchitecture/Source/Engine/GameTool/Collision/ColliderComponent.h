#pragma once

#include "../Component.h"
#include "../Vector/Vector4.h"

class Renderer;

class ColliderComponent : public Component
{
public:
	void OnStart() override;
	void OnEnd() override;

	virtual bool Collision(const ColliderComponent* pComponent) = 0;
	virtual void DebugRender(Renderer* rRenderer) = 0;

	//Variables
	Color mColor{ 255,0,0,255 };
};

