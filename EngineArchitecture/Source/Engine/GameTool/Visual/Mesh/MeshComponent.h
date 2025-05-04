#pragma once

#include "Engine/GameTool/Utility/Matrix/Matrix4.h"
#include "Engine/GameTool/Visual/Render/RenderComponent.h"

class Mesh;
class IRenderer;

/*
MeshComponent is a renderable component that holds a reference to a Mesh.
It is responsible for rendering the mesh using the transform of its owning actor.
This component also supports texture selection via index and texture tiling adjustments.
 */
class MeshComponent : public RenderComponent
{
public:
	/*
	 * Constructs a MeshComponent and assigns it to an owning Actor.
	 * @param pOwner Pointer to the Actor that owns this component.
	 * @param pMesh Pointer to the Mesh to render.
	 */
	MeshComponent(Actor* pOwner, Mesh* pMesh);

	/*
	 * Renders the mesh using the renderer interface.
	 * Applies the world transform of the owning actor and texture tiling before rendering.
	 * @param rRenderer Reference to the renderer responsible for drawing.
	 */
	void Render(IRenderer* rRenderer) override;
	/*
	 * Returns the render type of the component, which is World for MeshComponent.
	 * Used to determine how and where in the pipeline the object should be rendered.
	 * @return RenderType::World
	 */
	RenderType GetRenderType() override;

	/*
	 * Sets the mesh that this component will render.
	 * @param pMesh Reference to the Mesh object.
	 */
	virtual void SetMesh(Mesh& pMesh);

	/*
	 * Sets the index of the texture to be used from the mesh's texture list.
	 * @param pTextureIndex The index of the texture to use.
	 */
	void SetTextureIndex(size_t pTextureIndex);
	/*
	 * Sets the tiling factor for the mesh's texture.
	 * This controls how many times the texture is repeated across the surface.
	 * @param x Tiling amount in the X direction.
	 * @param y Tiling amount in the Y direction.
	 */
	void SetTextureTiling(float x, float y);

protected:
	Mesh* mMesh; // Pointer to the mesh to render
	size_t mTextureIndex; // Index of the texture to apply from the mesh's texture list

	Vector2 mTiling = Vector2::ONE; // Texture tiling factor (1,1 means no tiling)
};

