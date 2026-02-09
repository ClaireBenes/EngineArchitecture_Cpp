#include "PilotController.h"

#include "Engine/GameTool/Utility/Maths.h"
#include "Engine/GameTool/Actor.h"
#include "Engine/Manager/InputManager.h"
#include "Engine/Engine.h"

#include "Game/Actors/Doom/Projectile.h"
#include "Game/Actors/TheDescent/TheDescentPlayer.h"

#include "Engine/Engine.h"

PilotController::PilotController(Actor* pActor) : MoveComponent(pActor)
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

	mPlayer = static_cast<TheDescentPlayer*>(mOwner);
}

PilotController::~PilotController()
{
	InputManager::Instance().UnSubscribeToAllEvents(this);
}

void PilotController::Update()
{
	if (!Maths::NearZero(mRotationSpeed.MagnitudeSqr()))
	{
		Quaternion rotation = mOwner->mTransform->mRotation + Quaternion(mOwner->mTransform->Forward(), mRotationSpeed.z * Time::deltaTime);
		rotation = rotation + Quaternion(mOwner->mTransform->Right(), mRotationSpeed.y * Time::deltaTime);
		rotation = rotation + Quaternion(mOwner->mTransform->Up(), mRotationSpeed.x * Time::deltaTime);

		rotation.Normalize();
		mOwner->mTransform->mRotation = rotation;
	}

	if (!Maths::NearZero(mSpeed.Magnitude() + mVelocity.Magnitude()))
	{
		// Apply friction to velocity
		mVelocity.x -= mVelocity.x * Time::deltaTime * mFriction;
		mVelocity.z -= mVelocity.z * Time::deltaTime * mFriction;

		mOwner->mTransform->mPosition = GetDesiredPos();
	}

	int mouseDeltaX, mouseDeltaY;
	SDL_GetRelativeMouseState(&mouseDeltaX, &mouseDeltaY);

	SetRotationSpeed(Vector3(mouseDeltaX / 10, mouseDeltaY / 10, inputDirection.x));
}

void PilotController::OnNotify(SDL_Event& pEvent)
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
					inputDirection.x -= 0.5f;
					break;
				case SDLK_LEFT:
				case SDLK_q:
					inputDirection.x += 0.5f;
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
					inputDirection.x += 0.5f;
					break;
				case SDLK_LEFT:
				case SDLK_q:
					inputDirection.x -= 0.5f;
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
	Vector3 speed = //inputDirectionNormalized.x * Vector3::Right + 
		inputDirectionNormalized.y * Vector3::Forward +
		inputDirectionNormalized.z * Vector3::Up;
	speed *= mMovementSpeed;
	SetSpeed(speed);

}

Vector3 PilotController::GetDesiredPos()
{
	Vector3 desiredPosition = mOwner->mTransform->mPosition
		+ (mOwner->mTransform->Right() * mSpeed.x
			+ mOwner->mTransform->Up() * mSpeed.y
			+ mOwner->mTransform->Forward() * mSpeed.z) * Time::deltaTime + mVelocity;
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

void PilotController::OnMousePress(SDL_MouseButtonEvent& event)
{
	if(event.button == SDL_BUTTON_LEFT && mPlayer)
	{
		Projectile* newProjectile = new Projectile();
		newProjectile->SetPlayer(mOwner);
		mOwner->mScene->AddActor(newProjectile);

		mPlayer->Shoot();
	}
}
