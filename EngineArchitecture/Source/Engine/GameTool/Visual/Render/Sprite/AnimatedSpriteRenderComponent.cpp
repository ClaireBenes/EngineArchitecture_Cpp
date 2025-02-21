#include "AnimatedSpriteRenderComponent.h"

#include "Engine/Time.h"

AnimatedSpriteRenderComponent::AnimatedSpriteRenderComponent(Actor* pOwner, int pDrawOrder) :
SpriteRenderComponent(pOwner, pDrawOrder), mCurrentFrame(0.0f), mAnimFps(24.0f)
{

}

AnimatedSpriteRenderComponent::~AnimatedSpriteRenderComponent()
{
}

void AnimatedSpriteRenderComponent::SetAnimationFps(float pFps)
{
	mAnimFps = pFps;
}

void AnimatedSpriteRenderComponent::SetCurrentAnimation(std::string pAnimation)
{
	if (mTextureMap.find(pAnimation) != mTextureMap.end()) 
	{
		mCurrentAnimation = pAnimation;
	}
}

void AnimatedSpriteRenderComponent::AddAnimation(std::string pName, std::vector<Texture> pTextures)
{
	mTextureMap.emplace(pName, pTextures);
}

void AnimatedSpriteRenderComponent::Update()
{
	SpriteRenderComponent::Update();

	if (mCurrentAnimation.empty()) 
	{
		return;
	}

	if(mTextureMap[mCurrentAnimation].size() == 0)
	{
		return;
	}

	mCurrentFrame += mAnimFps * Time::deltaTime;
	while(mCurrentFrame >= mTextureMap[mCurrentAnimation].size())
	{
		mCurrentFrame -= mTextureMap[mCurrentAnimation].size();
	}

	SetTexture(mTextureMap[mCurrentAnimation][static_cast< int >( mCurrentFrame )]);
}


float AnimatedSpriteRenderComponent::GetAnimationFps() const
{
	return mAnimFps;
}