#include "PlatformerPlayerController.h"

#include "Engine/GameTool/Actor.h"
#include "Engine/GameTool/Visual/Render/Sprite/SpriteRenderComponent.h"
#include "Engine/GameTool/Visual/Render/Sprite/AnimatedSpriteRenderComponent.h"


#include "Engine/Renderer/IRenderer.h"
#include "Engine/Manager/InputManager.h"

PlatformerPlayerController::PlatformerPlayerController(Actor* pActor) : MoveComponent(pActor), mSpriteRenderComponent(nullptr)
{
	InputManager::Instance().SubscribeToKey(SDLK_q, this);
	InputManager::Instance().SubscribeToKey(SDLK_d, this);
	InputManager::Instance().SubscribeToKey(SDLK_SPACE, this);

	InputManager::Instance().SubscribeToKey(SDLK_LEFT, this);
	InputManager::Instance().SubscribeToKey(SDLK_RIGHT, this);
	InputManager::Instance().SubscribeToKey(SDLK_UP, this);
}

void PlatformerPlayerController::OnNotify(SDL_Event& pEvent)
{
	switch (pEvent.type)
	{
	case SDL_KEYDOWN:
	{
		Vector3 direction = Vector3::Zero;
		if (pEvent.key.keysym.sym == SDLK_SPACE || pEvent.key.keysym.sym == SDLK_UP)
		{
			if (!mIsJumping) 
			{
				direction.y = 1;
				AddForce({GetSpeed().x / 75, mForce.y, 0.0f});
				mIsJumping = true;

				mSpriteRenderComponent->SetCurrentAnimation("Jump");
			}
		}
		if (pEvent.key.keysym.sym == SDLK_RIGHT || pEvent.key.keysym.sym == SDLK_d)
		{
			direction.x = 1;

			mSpriteRenderComponent->mFlip = IRenderer::Flip::None;
			mSpriteRenderComponent->SetCurrentAnimation("Walk");
		}
		if (pEvent.key.keysym.sym == SDLK_LEFT || pEvent.key.keysym.sym == SDLK_q)
		{
			direction.x = -1;

			mSpriteRenderComponent->mFlip = IRenderer::Flip::Horizontal;
			mSpriteRenderComponent->SetCurrentAnimation("Walk");
		}

		SetSpeed(150.0f * direction);

		break;
	}

	case SDL_KEYUP:
		if (pEvent.key.keysym.sym == SDLK_RIGHT || pEvent.key.keysym.sym == SDLK_d || pEvent.key.keysym.sym == SDLK_LEFT || pEvent.key.keysym.sym == SDLK_q)
		{
			SetSpeed(Vector3::Zero);
			mVelocity = 0;
			mSpriteRenderComponent->SetCurrentAnimation("Idle");
		}
		if (pEvent.key.keysym.sym == SDLK_SPACE || pEvent.key.keysym.sym == SDLK_UP) 
		{
			SetSpeed({GetSpeed().x, 0.0f, 0.0f});
			mIsJumping = false;
		}
		break;

	default:
		break;
	}
}

void PlatformerPlayerController::OnStart()
{
	mSpriteRenderComponent = mOwner->GetComponentOfType<AnimatedSpriteRenderComponent>();
	if (mSpriteRenderComponent == nullptr) 
	{
		Log::Error(LogType::Application, "The actor doen't have a SpriteRenderComponent");
	}
}
