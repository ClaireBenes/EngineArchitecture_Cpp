#pragma once

#include "Engine/GameTool/Component.h"
#include "Engine/GameTool/Utility/Vector/Vector4.h"

class IRenderer;

enum class RenderType
{
	World,
	Viewport
};

class RenderComponent : public Component
{
public:
	RenderComponent(Actor* pOwner);

	void OnStart() override;
	void OnEnd() override;

	virtual void Render(IRenderer* rRenderer) = 0;
	virtual RenderType GetRenderType() = 0;
	virtual int GetDrawOrder() const;

	//Variables
	Color mColor{ 255,255,255,255 };
};

