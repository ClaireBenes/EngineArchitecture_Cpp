#pragma once

#include "Engine/GameTool/Utility/Matrix/Matrix4.h"
#include "Engine/GameTool/Visual/Render/RenderComponent.h"

class Mesh;
class IRenderer;

class MeshComponent : public RenderComponent
{
public:
	MeshComponent(Actor* pOwner, Mesh* pMesh);

	void Render(IRenderer* rRenderer) override;
	RenderType GetRenderType() override;

	virtual void SetMesh(Mesh& pMesh);

	void SetTextureIndex(size_t pTextureIndex);
	void SetTextureTiling(float x, float y);

protected:
	Mesh* mMesh;
	size_t mTextureIndex;

	Vector2 mTiling = Vector2::ONE;
};

