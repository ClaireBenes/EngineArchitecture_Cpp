#include "SpriteRenderComponent.h"

#include "Engine/GameTool/Actor.h"

SpriteRenderComponent::SpriteRenderComponent(Actor* pOwner, int pDrawOrder):
mDrawOrder(pDrawOrder),
mTexWidth(0),
mTexHeight(0)
{
	SetOwner(pOwner);
	AddSprite();
}

SpriteRenderComponent::SpriteRenderComponent(Actor* pOwner, const Texture& pTexture, int pDrawOrder):
mTexture(pTexture),
mDrawOrder(pDrawOrder),
mTexWidth(pTexture.GetWidth()),
mTexHeight(pTexture.GetHeight())
{
	SetOwner(pOwner);
	AddSprite();
}

SpriteRenderComponent::~SpriteRenderComponent()
{
	mOwner->mScene->GetRenderer()->RemoveSprite(this);
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
	tempRectangle.position += mOwner->mTransform.mPosition;

	pRenderer->DrawSprite(*mOwner, mTexture, tempRectangle, mFlip);
}

void SpriteRenderComponent::AddSprite()
{
	mOwner->mScene->GetRenderer()->AddSprite(this);
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
