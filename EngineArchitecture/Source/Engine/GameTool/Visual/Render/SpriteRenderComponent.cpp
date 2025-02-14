#include "SpriteRenderComponent.h"

#include "Engine/GameTool/Actor.h"
#include "Engine/Renderer.h"

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

	pRenderer->DrawSprite(*mOwner, mTexture, tempRectangle, Renderer::Flip::None);

}

void SpriteRenderComponent::AddSprite()
{
	mOwner->mScene->GetRenderer()->AddSprite(this);
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
