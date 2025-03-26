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
		Quaternion newRotation = mOwner->mTransform->mRotation + Quaternion(Vector3::Up, mRotationSpeed.x * Time::deltaTime);
		newRotation.Normalize();
		mOwner->mTransform->mRotation = newRotation;

		Quaternion desiredRotation = mOwner->mTransform->mRotation + Quaternion(Vector3::Transform(Vector3::Right, newRotation), mRotationSpeed.y * Time::deltaTime);
		desiredRotation.Normalize();

		const float PITCH_LIMIT = 60.0f;
		float pitch = Maths::ToDeg(desiredRotation.GetPitch());

		if ((pitch > -PITCH_LIMIT && pitch < PITCH_LIMIT) || (pitch > 180 - PITCH_LIMIT) || (pitch < -180 + PITCH_LIMIT))
		{
			mOwner->mTransform->mRotation = desiredRotation;
		}
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
		// TODO: Maybe replace the 0 on the Z-axis
		mOwner->mTransform->mPosition = { desiredPosition.x, oldPosition.y, 0 };
		if (CheckCollision() == true)
		{
			newPosition.x = oldPosition.x;
			mVelocity.x = 0;
		}

		//Check collision on Y axis
		// TODO: Maybe replace the 0 on the Z-axis
		mOwner->mTransform->mPosition = { oldPosition.x, desiredPosition.y, 0 };
		if (CheckCollision() == true)
		{
			newPosition.y = oldPosition.y;
			mVelocity.y = 0;
		}

		// TODO: Check collision on Z-axis

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

		// TODO: Return ColliderComponent to know with whom you collided
		// Then use GetOwner() to retrieve the actor, then call GetComponentOfType<MoveComponent>().
		// With that, you can transfer your mVelocity to that one MoveComponent.
		mInCollision = physicManager.Collision(mCollidercomponent);
		return mInCollision;
	}

	return false;
}
