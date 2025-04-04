#pragma once

#include "../RenderComponent.h"

#include "Engine/GameTool/Visual/Texture.h"
#include "Engine/GameTool/Utility/Geometry/Rectangle.h"

#include "Engine/Renderer/IRenderer.h"

class SpriteRenderComponent : public RenderComponent
{
public:
	SpriteRenderComponent(Actor* pOwner, int pDrawOrder = 100);
	SpriteRenderComponent(Actor* pOwner, Texture* pTexture, int pDrawOrder = 100);

	SpriteRenderComponent() = delete;
	SpriteRenderComponent(const SpriteRenderComponent&) = delete;
	SpriteRenderComponent& operator= (const SpriteRenderComponent&) = delete;

	virtual void SetTexture(Texture* pTexture);
	virtual void Render(IRenderer* pRenderer) override;
	RenderType GetRenderType() override;

	void SetNewDimensions(float x, float y);
	void SetNewPositions(float x, float y);

	//Getters
	int GetDrawOrder() const override;
	int GetTexWidth() const;
	int GetTexHeight() const;

public:
	//Variables
	Rectangle mRectangle{ Vector2(-16,-16),Vector2(32,32) };
	IRenderer::Flip mFlip = IRenderer::Flip::None;

protected:
	Texture* mTexture;

	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};

