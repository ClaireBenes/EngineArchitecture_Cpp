#include "PlayerController.h"

#include "Engine/GameTool/Actor.h"
#include "Engine/GameTool/Visual/Render/Sprite/SpriteRenderComponent.h"

#include "Engine/Renderer/RendererSDL.h"
#include "Engine/Manager/InputManager.h"

PlayerController::PlayerController(Actor* pActor) : MoveComponent(pActor)
{
	InputManager::Instance().SubscribeToKey(SDLK_z, this);
	InputManager::Instance().SubscribeToKey(SDLK_q, this);
	InputManager::Instance().SubscribeToKey(SDLK_s, this);
	InputManager::Instance().SubscribeToKey(SDLK_d, this);

	InputManager::Instance().SubscribeToKey(SDLK_UP, this);
	InputManager::Instance().SubscribeToKey(SDLK_LEFT, this);
	InputManager::Instance().SubscribeToKey(SDLK_DOWN, this);
	InputManager::Instance().SubscribeToKey(SDLK_RIGHT, this);
}

void PlayerController::OnNotify(SDL_Event& pEvent)
{
	switch (pEvent.type) 
	{
	case SDL_KEYDOWN: 
	{
		Vector3 direction = Vector3::Zero;
		if (pEvent.key.keysym.sym == SDLK_UP || pEvent.key.keysym.sym == SDLK_z)
		{
			direction.y = 1;
		}
		if (pEvent.key.keysym.sym == SDLK_DOWN || pEvent.key.keysym.sym == SDLK_s)
		{
			direction.y = -1;
		}
		if (pEvent.key.keysym.sym == SDLK_RIGHT || pEvent.key.keysym.sym == SDLK_d)
		{
			direction.x = 1;

			mOwner->GetComponentOfType<SpriteRenderComponent>()->mFlip = RendererSDL::Flip::None;
		}
		if (pEvent.key.keysym.sym == SDLK_LEFT || pEvent.key.keysym.sym == SDLK_q)
		{
			direction.x = -1;

			mOwner->GetComponentOfType<SpriteRenderComponent>()->mFlip = RendererSDL::Flip::Horizontal;
		}

		SetSpeed(150.0f * direction);

		break;
	}
		
	case SDL_KEYUP:
		SetSpeed(Vector3::Zero);
		break;

	default:
		break;
	}
}


