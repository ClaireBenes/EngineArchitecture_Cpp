#include "AnimatedSpriteRenderComponent.h"

#include "Engine/Time.h"

AnimatedSpriteRenderComponent::AnimatedSpriteRenderComponent(Actor* pOwner, const std::vector<Texture>& pTexture, int pDrawOrder) :
SpriteRenderComponent(pOwner, pTexture[0], pDrawOrder), mCurrentFrame(0.0f), mAnimFps(24.0f)
{
	SetAnimationTextures(pTexture);
}

AnimatedSpriteRenderComponent::~AnimatedSpriteRenderComponent()
{
}

void AnimatedSpriteRenderComponent::SetAnimationTextures(const std::vector<Texture>& pTextures)
{
	mAnimationTextures = pTextures;
	if(mAnimationTextures.size() > 0)
	{
		SetTexture(mAnimationTextures[0]);
	}
}

void AnimatedSpriteRenderComponent::SetAnimationFps(float pFps)
{
	mAnimFps = pFps;
}

void AnimatedSpriteRenderComponent::Update()
{
	SpriteRenderComponent::Update();

	if(mAnimationTextures.size() == 0)
	{
		return;
	}

	mCurrentFrame += mAnimFps * Time::deltaTime;
	while(mCurrentFrame >= mAnimationTextures.size())
	{
		mCurrentFrame -= mAnimationTextures.size();
	}

	SetTexture(mAnimationTextures[static_cast< int >( mCurrentFrame )]);
}


float AnimatedSpriteRenderComponent::GetAnimationFps() const
{
	return mAnimFps;
}