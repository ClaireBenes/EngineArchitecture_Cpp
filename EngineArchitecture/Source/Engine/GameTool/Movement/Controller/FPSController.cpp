#include "FPSController.h"

#include "Engine/GameTool/Utility/Maths.h"
#include "Engine/GameTool/Actor.h"
#include "Engine/Manager/InputManager.h"
#include "Engine/Engine.h"

FPSController::FPSController(Actor* pActor) : MoveComponent(pActor)
{
	InputManager::Instance().SubscribeTo(SDLK_z, this);
	InputManager::Instance().SubscribeTo(SDLK_q, this);
	InputManager::Instance().SubscribeTo(SDLK_s, this);
	InputManager::Instance().SubscribeTo(SDLK_d, this);

	InputManager::Instance().SubscribeTo(SDLK_UP, this);
	InputManager::Instance().SubscribeTo(SDLK_LEFT, this);
	InputManager::Instance().SubscribeTo(SDLK_DOWN, this);
	InputManager::Instance().SubscribeTo(SDLK_RIGHT, this);
}

void FPSController::Update()
{
	MoveComponent::Update();

	int mouseDeltaX, mouseDeltaY;
	SDL_GetRelativeMouseState(&mouseDeltaX, &mouseDeltaY);

	if (mouseDeltaX != 0 || mouseDeltaY != 0)
	{
		SetRotationSpeed(Vector2(mouseDeltaX / 10, -mouseDeltaY / 10));
	}
	else
	{
		SetRotationSpeed(Vector2::ZERO);
	}

}

void FPSController::OnNotify(SDL_Event& pEvent)
{
	switch(pEvent.type)
	{

		case SDL_KEYDOWN:
		{
			if (pEvent.key.repeat) return;

			switch (pEvent.key.keysym.sym)
			{
				case SDLK_UP:
				case SDLK_z:
					inputDirection.y += 1.0f;
					break;
				case SDLK_DOWN:
				case SDLK_s:
					inputDirection.y -= 1.0f;
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					inputDirection.x -= 0.5f;
					break;
				case SDLK_LEFT:
				case SDLK_q:
					inputDirection.x += 0.5f;
					break;
			}
			break;
		}

		case SDL_KEYUP:
		{
			if (pEvent.key.repeat) return;

			switch (pEvent.key.keysym.sym)
			{
				case SDLK_UP:
				case SDLK_z:
					inputDirection.y -= 1.0f;
					break;
				case SDLK_DOWN:
				case SDLK_s:
					inputDirection.y += 1.0f;
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					inputDirection.x += 0.5f;
					break;
				case SDLK_LEFT:
				case SDLK_q:
					inputDirection.x -= 0.5f;
					break;
			}
			break;
		}
		default:
			break;
	}

	Vector3 inputDirectionNormalized = inputDirection.Normalized();
	Vector3 speed = inputDirectionNormalized.x * Vector3::Right + inputDirectionNormalized.y * Vector3::Forward;
	speed *= mMovementSpeed;
	SetSpeed(speed);
}
