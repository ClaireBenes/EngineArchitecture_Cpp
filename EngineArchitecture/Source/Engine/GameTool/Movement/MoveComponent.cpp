#include "MoveComponent.h"

#include "Engine/GameTool/Utility/Math.h"
#include "Engine/GameTool/Actor.h"

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

		Vector2 newPosition = mOwner->mTransform.mPosition;
			+ (mOwner->mTransform.Right() * mSpeed.x
				+ mOwner->GetTransform().Up() * mSpeed.y) * Time::deltaTime;
		mOwner->SetPosition(newPosition);
	}
}
