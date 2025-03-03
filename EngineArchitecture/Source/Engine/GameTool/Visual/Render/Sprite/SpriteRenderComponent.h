#pragma once

#include "../RenderComponent.h"

#include "Engine/GameTool/Visual/Texture.h"
#include "Engine/GameTool/Rectangle.h"

#include "Engine/Renderer/IRenderer.h"

class SpriteRenderComponent : public RenderComponent
{
public:
	SpriteRenderComponent(Actor* pOwner, int pDrawOrder = 100);
	SpriteRenderComponent(Actor* pOwner, const Texture& pTexture, int pDrawOrder = 100);
	virtual ~SpriteRenderComponent();

	SpriteRenderComponent() = delete;
	SpriteRenderComponent(const SpriteRenderComponent&) = delete;
	SpriteRenderComponent& operator= (const SpriteRenderComponent&) = delete;

	virtual void SetTexture(const Texture& pTexture);
	virtual void Render(IRenderer* pRenderer) override;
	void AddSprite();
	void SetNewDimensions(float x, float y);

	//Getters
	int GetDrawOrder() const;
	int GetTexWidth() const;
	int GetTexHeight() const;

public:
	//Variables
	Rectangle mRectangle{ Vector2(-16,-16),Vector2(32,32) };
	IRenderer::Flip mFlip = IRenderer::Flip::None;

protected:
	Texture mTexture;

	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};

