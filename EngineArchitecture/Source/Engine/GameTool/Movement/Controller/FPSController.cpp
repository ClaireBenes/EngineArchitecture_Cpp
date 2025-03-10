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

	InputManager::Instance().SubscribeTo(SDL_MOUSEMOTION, this);
}

void FPSController::Update()
{
	MoveComponent::Update();

	int mouseDeltaX, mouseDeltaY;
	SDL_GetRelativeMouseState(&mouseDeltaX, &mouseDeltaY);

	printf("%d %d\n", mouseDeltaX, mouseDeltaY);

}

void FPSController::OnNotify(SDL_Event& pEvent)
{
	float forwardSpeed = 0.0f;
	float angularSpeed = 0.0f;

	switch(pEvent.type)
	{
		case SDL_KEYDOWN:
		{
			if(pEvent.key.keysym.sym == SDLK_UP || pEvent.key.keysym.sym == SDLK_z)
			{
				forwardSpeed += 10.0f;
			}
			if(pEvent.key.keysym.sym == SDLK_DOWN || pEvent.key.keysym.sym == SDLK_s)
			{
				forwardSpeed -= 10.0f;
			}
			if(pEvent.key.keysym.sym == SDLK_RIGHT || pEvent.key.keysym.sym == SDLK_d)
			{
				angularSpeed += Maths::TWO_PI / 5;
			}
			if(pEvent.key.keysym.sym == SDLK_LEFT || pEvent.key.keysym.sym == SDLK_q)
			{
				angularSpeed -= Maths::TWO_PI / 5;
			}

			SetSpeed(forwardSpeed * Vector3::Forward);
			SetRotationSpeed(angularSpeed);

			break;
		}

		case SDL_KEYUP:
		{
			SetSpeed(Vector3::Zero);
			SetRotationSpeed(0.0f);

			break;
		}
		case SDL_MOUSEMOTION:
			if(pEvent.motion.x || pEvent.motion.y)
			{
				//printf("sdfgsdfsdg\n");
			}
			printf("HOOOOOOOO\n");
		default:
			break;
	}
}
