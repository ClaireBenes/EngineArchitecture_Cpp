#include "SpriteRenderComponent.h"

#include "Engine/GameTool/Actor.h"

SpriteRenderComponent::SpriteRenderComponent(Actor* pOwner, int pDrawOrder):
mDrawOrder(pDrawOrder),
mTexWidth(0),
mTexHeight(0),
RenderComponent(pOwner)
{
}

SpriteRenderComponent::SpriteRenderComponent(Actor* pOwner, const Texture& pTexture, int pDrawOrder):
mTexture(pTexture),
mDrawOrder(pDrawOrder),
mTexWidth(pTexture.GetWidth()),
mTexHeight(pTexture.GetHeight()),
RenderComponent(pOwner)
{
}

void SpriteRenderComponent::SetTexture(const Texture& pTexture)
{
	mTexture = pTexture;
	mTexture.UpdateInfo(mTexWidth, mTexHeight);
}

void SpriteRenderComponent::Render(IRenderer* pRenderer)
{
	if (mTexHeight == 0 || mTexWidth == 0) 
	{
		return;
	}
	//relative transform position
	Rectangle tempRectangle = mRectangle;
	tempRectangle.position.x += mOwner->mTransform->mPosition.x;
	tempRectangle.position.y += mOwner->mTransform->mPosition.y;

	pRenderer->DrawSprite(*mOwner, mTexture, tempRectangle, mFlip);
}

RenderType SpriteRenderComponent::GetRenderType()
{
	return RenderType::Viewport;
}

void SpriteRenderComponent::SetNewDimensions(float x, float y)
{
	mRectangle.dimensions.x = x;
	mRectangle.dimensions.y = y;
}

int SpriteRenderComponent::GetDrawOrder() const
{
	return mDrawOrder;
}

int SpriteRenderComponent::GetTexWidth() const
{
	return mTexWidth;
}

int SpriteRenderComponent::GetTexHeight() const
{
	return mTexHeight;
}
