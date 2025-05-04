#pragma once

#include "SpriteRenderComponent.h"

#include <vector>
#include <string>
#include <unordered_map>

/*
AnimatedSpriteRenderComponent extends SpriteRenderComponent to support
frame-based 2D sprite animations using a sequence of textures.
 */
class AnimatedSpriteRenderComponent : public SpriteRenderComponent
{
public:
	/*
	 * Constructs an animated sprite component with an optional draw order.
	 * @param pOwner The actor that owns this component.
	 * @param pDrawOrder Drawing priority (higher values render later).
	 */
	AnimatedSpriteRenderComponent(Actor* pOwner, int pDrawOrder = 100);

	/*
	 * Destructor for the animated sprite component.
	 */
	virtual ~AnimatedSpriteRenderComponent();

	// Deleted constructors and assignment operators to prevent copying.
	AnimatedSpriteRenderComponent() = delete;
	AnimatedSpriteRenderComponent(const AnimatedSpriteRenderComponent&) = delete;
	AnimatedSpriteRenderComponent& operator=(const AnimatedSpriteRenderComponent&) = delete;

	/*
	 * Sets the frame rate (FPS) for the animation.
	 * @param pFps Frames per second.
	 */
	void SetAnimationFps(float pFps);
	/*
	 * Changes the current animation to play, by name.
	 * If the animation is not found, it has no effect.
	 * @param pAnimation Name of the animation to play.
	 */
	void SetCurrentAnimation(std::string pAnimation);

	/*
	 * Adds a new animation consisting of a name and a sequence of textures.
	 * @param pName Name identifier for the animation.
	 * @param pTextures Vector of textures forming the animation frames.
	 */
	void AddAnimation(std::string pName, std::vector<Texture*> pTextures);

	/*
	 Updates the animation by progressing the current frame based on time.
	 */
	void Update() override;

	//Getters

	/*
	 * Gets the currently configured animation FPS.
	 * @return Frames per second (float).
	 */
	float GetAnimationFps() const;

private:
	std::unordered_map<std::string, std::vector<Texture*>> mTextureMap; // A map of animation names to sequences of texture pointers.
	std::string mCurrentAnimation; // The name of the currently playing animation.

	float mCurrentFrame; // The current float index into the frame sequence.
	float mAnimFps; // Animation playback speed in frames per second.

};

