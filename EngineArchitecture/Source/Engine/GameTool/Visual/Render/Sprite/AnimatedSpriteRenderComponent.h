#pragma once

#include "SpriteRenderComponent.h"
#include <vector>

class AnimatedSpriteRenderComponent : public SpriteRenderComponent
{
public:
	AnimatedSpriteRenderComponent(const std::vector<Texture>& pTexture, int pDrawOrder = 100);
	virtual ~AnimatedSpriteRenderComponent();
	AnimatedSpriteRenderComponent() = delete;
	AnimatedSpriteRenderComponent(const AnimatedSpriteRenderComponent&) = delete;
	AnimatedSpriteRenderComponent& operator=(const AnimatedSpriteRenderComponent&) = delete;

	void SetAnimationTextures(const std::vector<Texture>& pTextures);
	void SetAnimationFps(float pFps);

	void Update() override;

	//Getters
	float GetAnimationFps() const;

private:
	std::vector<Texture> mAnimationTextures;

	float mCurrentFrame;
	float mAnimFps;
};

