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

void SpriteRenderComponent::SetTexture(const Texture& pTexture)
{
	mTexture = pTexture;
	mTexture.UpdateInfo(mTexWidth, mTexHeight);
}

void SpriteRenderComponent::Render(Renderer* pRenderer)
{

	//SDL_Rect tempRect;
	//Transform2D transform = mOwner->mTransform;

	//tempRect.w = static_cast<int>(mTexture.GetWidth() * transform.mScale.x);
	//tempRect.h = static_cast<int>(mTexture.GetHeight() * transform.mScale.y);
	//tempRect.x = static_cast<int>(transform.mPosition.x - mTexWidth / 2.0f);
	//tempRect.y = static_cast<int>(transform.mPosition.y - mTexHeight / 2.0f);

	//relative transform position
	Rectangle tempRectangle = mRectangle;
	tempRectangle.position += mOwner->mTransform.mPosition;


	//Vector2 origin{ mTexWidth / 2.0f, mTexHeight / 2.0f };
	pRenderer->DrawSprite(mTexture, tempRectangle, mOwner);
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
