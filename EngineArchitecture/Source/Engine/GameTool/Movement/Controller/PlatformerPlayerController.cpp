#include "PlatformerPlayerController.h"

#include "Engine/GameTool/Actor.h"
#include "Engine/GameTool/Visual/Render/Sprite/SpriteRenderComponent.h"

#include "Engine/Renderer.h"

#include "Engine/Manager/InputManager.h"

PlatformerPlayerController::PlatformerPlayerController(Actor* pActor) : MoveComponent(pActor)
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
			if (!mIsJumping) 
			{
				direction.y = 1;
				AddForce({GetSpeed().x / 75, mForce.y});
				mIsJumping = true;
			}

		}
		if (pEvent.key.keysym.sym == SDLK_RIGHT || pEvent.key.keysym.sym == SDLK_d)
		{
			direction.x = 1;

			mOwner->GetComponentOfType<SpriteRenderComponent>()->mFlip = Renderer::Flip::None;
		}
		if (pEvent.key.keysym.sym == SDLK_LEFT || pEvent.key.keysym.sym == SDLK_q)
		{
			direction.x = -1;

			mOwner->GetComponentOfType<SpriteRenderComponent>()->mFlip = Renderer::Flip::Horizontal;
		}

		SetSpeed(150.0f * direction);

		break;
	}

	case SDL_KEYUP:
		SetSpeed(Vector2::ZERO);
		//mVelocity.x = 0;
		
		mIsJumping = false;

		break;

	default:
		break;
	}
}
