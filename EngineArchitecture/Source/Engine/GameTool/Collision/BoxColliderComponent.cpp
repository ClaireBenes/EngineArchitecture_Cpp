#include "BoxColliderComponent.h"

#include "Engine/GameTool/Actor.h"
#include "Engine/Renderer/RendererGL.h"

BoxColliderComponent::BoxColliderComponent(Actor* pOwner, Box pBox) : mBox(pBox), ColliderComponent(pOwner)
{
}

void BoxColliderComponent::DebugRender(IRenderer* pRenderer)
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	Matrix4 cubeTransform = Matrix4::CreateScale(mBox.GetSize() * mOwner->mTransform->mScale * 0.5f);
	cubeTransform *= Matrix4::CreateFromQuaternion(Quaternion::Identity);
	cubeTransform *= Matrix4::CreateTranslation(mOwner->mTransform->mPosition + mBox.GetCenter() * mOwner->mTransform->mScale);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	pRenderer->DrawMesh(RendererGL::GetCubeMesh(), 0, cubeTransform);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

bool BoxColliderComponent::Collision(const ColliderComponent* pComponent)
{
	if (const BoxColliderComponent* pBoxComponent = dynamic_cast<const BoxColliderComponent*>(pComponent))
	{
		return Box::Collision(pBoxComponent->GetWorldBox(), GetWorldBox());
	}
	return false;
}

Box BoxColliderComponent::GetWorldBox() const
{
	Box worldBox = mBox;
	worldBox.min = worldBox.min * mOwner->mTransform->mScale + mOwner->mTransform->mPosition;
	worldBox.max = worldBox.max * mOwner->mTransform->mScale + mOwner->mTransform->mPosition;

	return worldBox;
}
