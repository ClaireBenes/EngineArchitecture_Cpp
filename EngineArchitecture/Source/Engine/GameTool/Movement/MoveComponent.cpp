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
		mOwner->mTransform->mPosition = GetDesiredPos();
	}
}

Vector3 MoveComponent::GetDesiredPos()
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

void MoveComponent::SetCollider(ColliderComponent* pCollider)
{
	mCollidercomponent = pCollider;
}

ColliderComponent* MoveComponent::CheckCollision()
{
	if (mCollidercomponent != nullptr)
	{
		PhysicManager& physicManager = PhysicManager::Instance();
		ColliderComponent* collidedComponent = physicManager.Collision(mCollidercomponent);

		if (collidedComponent != nullptr)
		{
			if (collidedComponent->GetOwner()->GetComponentOfType<MoveComponent>() != nullptr)
			{
				Vector3 collisionNormal = physicManager.GetCollisionNormal(mCollidercomponent, collidedComponent);;
				float impactStrength = mVelocity.Dot(mVelocity, collisionNormal);

				// Ensure some movement
				if (impactStrength < 0.3f)
				{
					impactStrength = 0.2f; 
				}

				collidedComponent->GetOwner()->GetComponentOfType<MoveComponent>()->mVelocity += collisionNormal * impactStrength;

				mVelocity *= mFriction;
			}
			return collidedComponent;		
		}
		return nullptr;
	}
	return nullptr;
}
