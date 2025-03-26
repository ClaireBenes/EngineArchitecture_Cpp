#pragma once

#include "SpriteRenderComponent.h"

#include <vector>
#include <string>
#include <unordered_map>

class AnimatedSpriteRenderComponent : public SpriteRenderComponent
{
public:
	AnimatedSpriteRenderComponent(Actor* pOwner, int pDrawOrder = 100);
	virtual ~AnimatedSpriteRenderComponent();
	AnimatedSpriteRenderComponent() = delete;
	AnimatedSpriteRenderComponent(const AnimatedSpriteRenderComponent&) = delete;
	AnimatedSpriteRenderComponent& operator=(const AnimatedSpriteRenderComponent&) = delete;

	void SetAnimationFps(float pFps);
	void SetCurrentAnimation(std::string pAnimation);

	void AddAnimation(std::string pName, std::vector<Texture*> pTextures);

	void Update() override;

	//Getters
	float GetAnimationFps() const;

private:
	std::vector<Texture> mAnimationTextures;

	std::unordered_map<std::string, std::vector<Texture*>> mTextureMap;
	std::string mCurrentAnimation;

	float mCurrentFrame;
	float mAnimFps;

};

