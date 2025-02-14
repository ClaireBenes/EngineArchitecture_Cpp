#include "SpriteRenderComponent.h"

#include "Engine/GameTool/Actor.h"

SpriteRenderComponent::SpriteRenderComponent(Texture& pTexture, int pDrawOrder):
mTexture(pTexture),
mDrawOrder(pDrawOrder),
mTexWidth(pTexture.GetWidth()),
mTexHeight(pTexture.GetHeight())
{

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

void SpriteRenderComponent::Render(Renderer* pRenderer)
{
	//relative transform position
	Rectangle tempRectangle = mRectangle;
	tempRectangle.position += mOwner->mTransform.mPosition;

	pRenderer->DrawSprite(*mOwner, mTexture, tempRectangle, mFlip);
}

void SpriteRenderComponent::AddSprite()
{
	mOwner->mScene->GetRenderer()->AddSprite(this);
}

void SpriteRenderComponent::SetNewDimensions(int x, int y)
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
