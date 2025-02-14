#pragma once

#include "../RenderComponent.h"

#include "Engine/GameTool/Visual/Texture.h"
#include "Engine/GameTool/Rectangle.h"

#include "Engine/Renderer.h"

class SpriteRenderComponent : public RenderComponent
{
public:
	SpriteRenderComponent(const Texture& pTexture, int pDrawOrder = 100);
	virtual ~SpriteRenderComponent();

	SpriteRenderComponent() = delete;
	SpriteRenderComponent(const SpriteRenderComponent&) = delete;
	SpriteRenderComponent& operator= (const SpriteRenderComponent&) = delete;

	virtual void SetTexture(const Texture& pTexture);
	virtual void Render(Renderer* pRenderer) override;
	void AddSprite();
	void SetNewDimensions(int x, int y);

	//Getters
	int GetDrawOrder() const;
	int GetTexWidth() const;
	int GetTexHeight() const;

public:
	//Variables
	Rectangle mRectangle{ Vector2(-16,-16),Vector2(32,32) };
	Renderer::Flip mFlip = Renderer::Flip::None;

protected:
	Texture mTexture;

	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};

