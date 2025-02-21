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
	if (!Maths::NearZero(mSpeed.SqrLength()))
	{
		Vector2 newPosition = mOwner->mTransform.mPosition
			+ (mOwner->mTransform.Right() * mSpeed.x
				+ mOwner->mTransform.Up() * mSpeed.y) * Time::deltaTime;
		Vector2 oldPosition = mOwner->mTransform.mPosition;

		mOwner->mTransform.mPosition = newPosition;
		if (CheckCollision() == true)
		{
			mOwner->mTransform.mPosition = oldPosition;
		}
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
		//printf("IN COLLISION | ");

		PhysicManager& physicManager = PhysicManager::Instance();

		return physicManager.Collision(mCollidercomponent);
	}

	return false;
}
