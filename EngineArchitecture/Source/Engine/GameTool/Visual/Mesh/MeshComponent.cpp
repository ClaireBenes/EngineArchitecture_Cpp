#include "MeshComponent.h"

#include "Mesh.h"
#include "Engine/GameTool/Scene.h"
#include "Engine/GameTool/Actor.h"
#include "Engine/Renderer/IRenderer.h"
#include "Engine/Vertex/VertexArray.h"

MeshComponent::MeshComponent(Actor* pOwner, Mesh* pMesh) : mMesh(pMesh), mTextureIndex(0), RenderComponent(pOwner)
{
}

void MeshComponent::Render(IRenderer* rRenderer)
{
	mOwner->mTransform->ComputeWorldTransform();
	rRenderer->DrawMesh(mMesh, mTextureIndex, mOwner->mTransform->GetWorldTransform(), mTiling);
}

RenderType MeshComponent::GetRenderType()
{
	return RenderType::World;
}

void MeshComponent::SetMesh(Mesh& pMesh)
{
	mMesh = &pMesh;
}

void MeshComponent::SetTextureIndex(size_t pTextureIndex)
{
	mTextureIndex = pTextureIndex;
}

void MeshComponent::SetTextureTiling(float x, float y)
{
	mTiling = Vector2(x, y);
}
