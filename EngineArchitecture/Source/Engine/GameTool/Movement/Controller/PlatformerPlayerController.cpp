#include "PlatformerPlayerController.h"

#include "Engine/GameTool/Actor.h"
#include "Engine/GameTool/Visual/Render/Sprite/SpriteRenderComponent.h"
#include "Engine/GameTool/Visual/Render/Sprite/AnimatedSpriteRenderComponent.h"


#include "Engine/Renderer/RendererSDL.h"

#include "Engine/Manager/InputManager.h"

PlatformerPlayerController::PlatformerPlayerController(Actor* pActor) : MoveComponent(pActor), mSpriteRenderComponent(nullptr)
{
	InputManager::Instance().SubscribeTo(SDLK_q, this);
	InputManager::Instance().SubscribeTo(SDLK_d, this);
	InputManager::Instance().SubscribeTo(SDLK_SPACE, this);

	InputManager::Instance().SubscribeTo(SDLK_LEFT, this);
	InputManager::Instance().SubscribeTo(SDLK_RIGHT, this);
	InputManager::Instance().SubscribeTo(SDLK_UP, this);
}

void PlatformerPlayerController::OnNotify(SDL_Event& pEvent)
{
	switch (pEvent.type)
	{
	case SDL_KEYDOWN:
	{
		Vector2 direction = Vector2::ZERO;
		if (pEvent.key.keysym.sym == SDLK_SPACE || pEvent.key.keysym.sym == SDLK_UP)
		{
			if (!mIsJumping && mInCollision) 
			{
				direction.y = 1;
				AddForce({GetSpeed().x / 75, mForce.y});
				mIsJumping = true;

				mSpriteRenderComponent->SetCurrentAnimation("Jump");
			}
		}
		if (pEvent.key.keysym.sym == SDLK_RIGHT || pEvent.key.keysym.sym == SDLK_d)
		{
			direction.x = 1;

			mSpriteRenderComponent->mFlip = RendererSDL::Flip::None;
			mSpriteRenderComponent->SetCurrentAnimation("Walk");
		}
		if (pEvent.key.keysym.sym == SDLK_LEFT || pEvent.key.keysym.sym == SDLK_q)
		{
			direction.x = -1;

			mSpriteRenderComponent->mFlip = RendererSDL::Flip::Horizontal;
			mSpriteRenderComponent->SetCurrentAnimation("Walk");
		}

		SetSpeed(150.0f * direction);

		break;
	}

	case SDL_KEYUP:
		if (pEvent.key.keysym.sym == SDLK_RIGHT || pEvent.key.keysym.sym == SDLK_d || pEvent.key.keysym.sym == SDLK_LEFT || pEvent.key.keysym.sym == SDLK_q)
		{
			SetSpeed(Vector2::ZERO);
			mVelocity = 0;
			mSpriteRenderComponent->SetCurrentAnimation("Idle");
		}
		if (pEvent.key.keysym.sym == SDLK_SPACE || pEvent.key.keysym.sym == SDLK_UP) 
		{
			SetSpeed({GetSpeed().x, 0});
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
