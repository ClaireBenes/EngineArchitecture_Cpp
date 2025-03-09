#include "Transform.h"

#include "Engine/GameTool/Actor.h"

Transform::Transform(Vector3 pPosition, Vector3 pScale, float pRotation)
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
	mWorldTransform *= Matrix4::CreateRotationX(mRotation.x);
	mWorldTransform *= Matrix4::CreateRotationY(mRotation.y);
	mWorldTransform *= Matrix4::CreateRotationZ(mRotation.z);
	mWorldTransform *= Matrix4::CreateTranslation(mPosition);

	mOwner->UpdateComponentsTransform();
}

const Matrix4& Transform::GetWorldTransform() const
{
	return mWorldTransform;
}
