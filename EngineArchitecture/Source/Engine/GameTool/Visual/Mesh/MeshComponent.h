#pragma once

#include "Engine/GameTool/Utility/Matrix/Matrix4.h"
#include "Engine/GameTool/Visual/Render/RenderComponent.h"

class Mesh;
class IRenderer;

/**
 * @brief MeshComponent is a renderable component that holds a reference to a Mesh.
 * It is responsible for rendering the mesh using the transform of its owning actor.
 * This component also supports texture selection via index and texture tiling adjustments.
 */
class MeshComponent : public RenderComponent
{
public:
	/**
	 * @brief Constructs a MeshComponent and assigns it to an owning Actor.
	 * @param pOwner Pointer to the Actor that owns this component.
	 * @param pMesh Pointer to the Mesh to render.
	 */
	MeshComponent(Actor* pOwner, Mesh* pMesh);

	/**
	 * @brief Renders the mesh using the renderer interface.
	 * Applies the world transform of the owning actor and texture tiling before rendering.
	 * @param rRenderer Reference to the renderer responsible for drawing.
	 */
	void Render(IRenderer* rRenderer) override;
	/**
	 * @brief Returns the render type of the component, which is World for MeshComponent.
	 * Used to determine how and where in the pipeline the object should be rendered.
	 * @return RenderType::World
	 */
	RenderType GetRenderType() override;

	/**
	 * @brief Sets the mesh that this component will render.
	 * @param pMesh Reference to the Mesh object.
	 */
	virtual void SetMesh(Mesh& pMesh);

	/**
	 * @brief Sets the index of the texture to be used from the mesh's texture list.
	 * @param pTextureIndex The index of the texture to use.
	 */
	void SetTextureIndex(size_t pTextureIndex);
	/**
	 * @brief Sets the tiling factor for the mesh's texture.
	 * This controls how many times the texture is repeated across the surface.
	 * @param x Tiling amount in the X direction.
	 * @param y Tiling amount in the Y direction.
	 */
	void SetTextureTiling(float x, float y);

protected:
	/**
	 * @brief Pointer to the mesh to render
	 */
	Mesh* mMesh; 
	/**
	 * @brief Index of the texture to apply from the mesh's texture list
	 */
	size_t mTextureIndex; 

	/**
	 * @brief Texture tiling factor (1,1 means no tiling)
	 */
	Vector2 mTiling = Vector2::ONE;
};

