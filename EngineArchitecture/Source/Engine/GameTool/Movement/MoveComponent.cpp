#include "MoveComponent.h"

#include "Engine/GameTool/Utility/Math.h"
#include "Engine/GameTool/Actor.h"
#include "Engine/Log.h"

#include "Engine/GameTool/Collision/ColliderComponent.h"

#include "Engine/Manager/PhysicManager.h"

MoveComponent::MoveComponent(Actor* pOwner, int pUpdateOrder) :
	Component(pUpdateOrder), mSpeed(0.0f)
{
	SetOwner(pOwner);
}

Vector2 MoveComponent::GetSpeed() const
{
	return mSpeed;
}

void MoveComponent::SetSpeed(Vector2 pSpeed)
{
	mSpeed = pSpeed;
}

void MoveComponent::Update()
{
	if (mGravityDirection != Vector2::ZERO) 
	{
		mVelocity += mGravityDirection * Time::deltaTime;
	}

	if (!Maths::NearZero(mSpeed.SqrLength() + mVelocity.SqrLength()))
	{
		Vector2 desiredPosition = mOwner->mTransform.mPosition
			+ (mOwner->mTransform.Right() * mSpeed.x
				+ mOwner->mTransform.Up() * mSpeed.y) * Time::deltaTime + mVelocity;
		Vector2 oldPosition = mOwner->mTransform.mPosition;

		Vector2 newPosition = desiredPosition;

		//Check collision on X axis
		mOwner->mTransform.mPosition = { desiredPosition.x, oldPosition.y };
		if (CheckCollision() == true)
		{
			newPosition.x = oldPosition.x;
			mVelocity.x = 0;
		}

		//Check collision on Y axis
		mOwner->mTransform.mPosition = { oldPosition.x, desiredPosition.y };
		if (CheckCollision() == true)
		{
			newPosition.y = oldPosition.y;
			mVelocity.y = 0;
		}

		mOwner->mTransform.mPosition = newPosition;
	}
}

void MoveComponent::SetCollider(ColliderComponent* pCollider)
{
	mCollidercomponent = pCollider;
}

bool MoveComponent::CheckCollision()
{
	if (mCollidercomponent != nullptr)
	{
		PhysicManager& physicManager = PhysicManager::Instance();

		return physicManager.Collision(mCollidercomponent);
	}

	return false;
}
