#pragma once

#include "RenderComponent.h"

#include "Engine/Renderer/IRenderer.h"
#include "Engine/Shader/ShaderProgram.h"

class ScreenEffectRenderComponent : public RenderComponent
{
public:
	ScreenEffectRenderComponent(Actor* pOwner, int pDrawOrder = 100);

	// Deleted constructors and assignment operators to enforce non-copyable behavior.
	ScreenEffectRenderComponent() = delete;
	ScreenEffectRenderComponent(const ScreenEffectRenderComponent&) = delete;
	ScreenEffectRenderComponent& operator= (const ScreenEffectRenderComponent&) = delete;

	void Render(IRenderer* pRenderer) override;

	//Getters
	RenderType GetRenderType() override;

	ShaderProgram& GetShaderProgram();

	int GetDrawOrder() const override;

private:
	ShaderProgram mShaderProgram;

	int mDrawOrder;
};

