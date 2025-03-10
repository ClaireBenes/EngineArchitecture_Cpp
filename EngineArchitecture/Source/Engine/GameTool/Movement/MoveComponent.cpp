#include "MoveComponent.h"

#include "Engine/GameTool/Utility/Maths.h"
#include "Engine/GameTool/Actor.h"
#include "Engine/Log.h"

#include "Engine/GameTool/Collision/ColliderComponent.h"

#include "Engine/Manager/PhysicManager.h"

MoveComponent::MoveComponent(Actor* pOwner, int pUpdateOrder) :
	Component(pOwner, pUpdateOrder), mSpeed(0.0f)
{
}

Vector3 MoveComponent::GetSpeed() const
{
	return mSpeed;
}

void MoveComponent::SetSpeed(Vector3 pSpeed)
{
	mSpeed = pSpeed;
}

void MoveComponent::AddForce(Vector3 pForce)
{
	mVelocity += pForce;
}

Vector2 MoveComponent::GetRotationSpeed() const
{
	return mRotationSpeed;
}

void MoveComponent::SetRotationSpeed(Vector2 pRotationSpeed)
{
	mRotationSpeed = pRotationSpeed;
}

void MoveComponent::Update()
{
	if (mGravityDirection != Vector3::Zero)
	{
		mVelocity += mGravityDirection * Time::deltaTime;
	}

	if(!Maths::NearZero(mRotationSpeed.SqrLength()))
	{
		Quaternion newRotation = Quaternion::Concatenate(mOwner->mTransform->mRotation, Quaternion(Vector3::Up, mRotationSpeed.x * Time::deltaTime));
		mOwner->mTransform->mRotation = newRotation;

		//Quaternion desiredRotation = Quaternion::Concatenate(mOwner->mTransform->mRotation, Quaternion(Vector3::Right, mRotationSpeed.y * Time::deltaTime));
		//Quaternion oldPosition = mOwner->mTransform->mRotation;

		//float dif = desiredRotation.x - oldPosition.x;

		//if ((((desiredRotation.x * 100) >= -50) && dif < 0) || (((desiredRotation.x * 100) <= 50) && dif > 0))
		//{
		//	mOwner->mTransform->mRotation = desiredRotation;
		//}

		//printf("%f , %f\n", desiredRotation.x * 100, oldPosition.x * 100);
		//printf("%f\n", oldPosition.x * 100 - desiredRotation.x * 100);
	}

	if (!Maths::NearZero(mSpeed.MagnitudeSqr() + mVelocity.MagnitudeSqr()))
	{
		Vector3 desiredPosition = mOwner->mTransform->mPosition
			+ (mOwner->mTransform->Right() * mSpeed.x
				+ mOwner->mTransform->Up() * mSpeed.y
				+ mOwner->mTransform->Forward() * mSpeed.z) * Time::deltaTime + mVelocity;
		Vector3 oldPosition = mOwner->mTransform->mPosition;

		Vector3 newPosition = desiredPosition;

		//Check collision on X axis
		mOwner->mTransform->mPosition = { desiredPosition.x, oldPosition.y, 0 };
		if (CheckCollision() == true)
		{
			newPosition.x = oldPosition.x;
			mVelocity.x = 0;
		}

		//Check collision on Y axis
		mOwner->mTransform->mPosition = { oldPosition.x, desiredPosition.y, 0 };
		if (CheckCollision() == true)
		{
			newPosition.y = oldPosition.y;
			mVelocity.y = 0;
		}

		mOwner->mTransform->mPosition = newPosition;
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

		mInCollision = physicManager.Collision(mCollidercomponent);
		return mInCollision;
	}

	return false;
}
