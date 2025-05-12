#include "FPSController.h"

#include "Engine/GameTool/Utility/Maths.h"
#include "Engine/GameTool/Actor.h"
#include "Engine/Manager/InputManager.h"
#include "Engine/Engine.h"

#include "Game/Actors/Doom/Projectile.h"
#include "Game/Actors/Doom/DoomPlayer.h"

#include "Engine/Engine.h"

FPSController::FPSController(Actor* pActor) : MoveComponent(pActor)
{
	InputManager::Instance().SubscribeToKey(SDLK_z, this);
	InputManager::Instance().SubscribeToKey(SDLK_q, this);
	InputManager::Instance().SubscribeToKey(SDLK_s, this);
	InputManager::Instance().SubscribeToKey(SDLK_d, this);

	InputManager::Instance().SubscribeToKey(SDLK_UP, this);
	InputManager::Instance().SubscribeToKey(SDLK_LEFT, this);
	InputManager::Instance().SubscribeToKey(SDLK_DOWN, this);
	InputManager::Instance().SubscribeToKey(SDLK_RIGHT, this);

	InputManager::Instance().SubscribeToKey(SDLK_RETURN, this);
	InputManager::Instance().SubscribeToMouse(SDL_BUTTON_LEFT, this);

	mPlayer = static_cast<DoomPlayer*>(mOwner);
}

FPSController::~FPSController()
{
	InputManager::Instance().UnSubscribeToAllEvents(this);
}

void FPSController::Update()
{
	MoveComponent::Update();

	int mouseDeltaX, mouseDeltaY;
	SDL_GetRelativeMouseState(&mouseDeltaX, &mouseDeltaY);

	if (mouseDeltaX != 0 || mouseDeltaY != 0)
	{
		SetRotationSpeed(Vector2(mouseDeltaX / 10, mouseDeltaY / 10));
	}
	else
	{
		SetRotationSpeed(Vector2::ZERO);
	}
}

void FPSController::OnNotify(SDL_Event& pEvent)
{
	switch (pEvent.type)
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
					inputDirection.x += 0.5f;
					break;
				case SDLK_LEFT:
				case SDLK_q:
					inputDirection.x -= 0.5f;
					break;
				case SDLK_RETURN:
					if (mPlayer->mIsGameEnd) 
					{
						mPlayer->mIsGameEnd = false;
						mPlayer->mScene->Reload();
					}
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
					inputDirection.x -= 0.5f;
					break;
				case SDLK_LEFT:
				case SDLK_q:
					inputDirection.x += 0.5f;
					break;
			}
			break;
		}

		case SDL_MOUSEBUTTONDOWN:
		{
			OnMousePress(pEvent.button);
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

Vector3 FPSController::GetDesiredPos()
{
	Vector3 desiredPosition = mOwner->mTransform->mPosition
		+ (mOwner->mTransform->Right() * mSpeed.x
			+ mOwner->mTransform->Up() * mSpeed.y
			+ mOwner->mTransform->Forward().Normalized2D() * mSpeed.z) * Time::deltaTime + mVelocity;
	Vector3 oldPosition = mOwner->mTransform->mPosition;

	Vector3 newPosition = desiredPosition;

	//Check collision on X axis
	mOwner->mTransform->mPosition = { desiredPosition.x, oldPosition.y, oldPosition.z };
	if (CheckCollision() != nullptr)
	{
		newPosition.x = oldPosition.x;
		mVelocity.x = 0;
	}

	//Check collision on Y axis
	mOwner->mTransform->mPosition = { oldPosition.x, desiredPosition.y, oldPosition.z };
	if (CheckCollision() != nullptr)
	{
		newPosition.y = oldPosition.y;
		mVelocity.y = 0;
	}

	mOwner->mTransform->mPosition = { oldPosition.x, oldPosition.y, desiredPosition.z };
	if (CheckCollision() != nullptr)
	{
		newPosition.z = oldPosition.z;
		mVelocity.z = 0;
	}

	return newPosition;
}

void FPSController::OnMousePress(SDL_MouseButtonEvent& event)
{
	if(event.button == SDL_BUTTON_LEFT && mPlayer)
	{
		if(mPlayer->GetAmmo() > 0)
		{
			Projectile* newProjectile = new Projectile();
			newProjectile->SetPlayer(mOwner);
			mOwner->mScene->AddActor(newProjectile);

			mPlayer->Shoot();
		}
	}
}
