#pragma once

#include "RenderComponent.h"

#include "../Texture.h"
#include "../../Rectangle.h"

#include "Engine/Renderer.h"

class SpriteRenderComponent : public RenderComponent
{
public:
	SpriteRenderComponent(Texture& pTexture, int pDrawOrder = 100);
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

	//Variables
	Rectangle mRectangle{ Vector2(-16,-16),Vector2(32,32) };

protected:
	Texture mTexture;
	Renderer::Flip mFlip = Renderer::Flip::None;

	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};

