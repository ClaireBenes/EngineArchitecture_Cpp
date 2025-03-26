#pragma once

#include "../Component.h"
#include "Engine/GameTool/Utility/Vector/Vector4.h"

#include "Engine/Renderer/DebugRenderInterface.h"

class IRendererSDL;

class ColliderComponent : public Component, public DebugRenderInterface
{
public:
	ColliderComponent(Actor* pOwner);

	void OnStart() override;
	void OnEnd() override;

	virtual bool Collision(const ColliderComponent* pComponent) = 0;

	//Variables
	Color mColor{ 255,0,0,255 };
};

