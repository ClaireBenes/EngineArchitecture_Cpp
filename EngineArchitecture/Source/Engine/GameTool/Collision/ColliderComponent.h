#pragma once

#include "../Component.h"
#include "Engine/GameTool/Utility/Vector/Vector4.h"

class IRendererSDL;

class ColliderComponent : public Component
{
public:
	ColliderComponent(Actor* pOwner);

	void OnStart() override;

	virtual bool Collision(const ColliderComponent* pComponent) = 0;

	// TODO : Have it work with the draw Refactor
	virtual void DebugRender(IRenderer* rRenderer) = 0;

	//Variables
	Color mColor{ 255,0,0,255 };
};

