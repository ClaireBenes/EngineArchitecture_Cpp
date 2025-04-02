#include "Transform.h"

#include "Engine/GameTool/Actor.h"

Transform::Transform(Actor* pOwner, Vector3 pPosition, Vector3 pScale, Quaternion pRotation)
	: Component(pOwner)
{
	mPosition = pPosition;
	mScale = pScale;
	mRotation = pRotation;
}

void Transform::ComputeWorldTransform()
{
	if (!NeedRecomputeWorldTransform) 
	{
		return;
	} 

	//NeedRecomputeWorldTransform = false;

	mWorldTransform = Matrix4::CreateScale(mScale);
	mWorldTransform *= Matrix4::CreateFromQuaternion(mRotation);
	mWorldTransform *= Matrix4::CreateTranslation(mPosition);

	mOwner->UpdateComponentsTransform();
}

const Matrix4& Transform::GetWorldTransform() const
{
	return mWorldTransform;
}

void Transform::LookAt(Vector3 target)
{
	mRotation = Quaternion::LookAt(mPosition, target, Vector3::Up);
}

void Transform::RotatePitch(float degrees)
{
	mRotation = Quaternion::Concatenate(mRotation, Quaternion(Vector3::Right, Maths::ToRad(degrees)));
}

void Transform::RotateYaw(float degrees)
{
	mRotation = Quaternion::Concatenate(mRotation, Quaternion(Vector3::Up, Maths::ToRad(degrees)));
}

void Transform::RotateRoll(float degrees)
{
	mRotation = Quaternion::Concatenate(mRotation, Quaternion(Vector3::Forward, Maths::ToRad(degrees)));
}
