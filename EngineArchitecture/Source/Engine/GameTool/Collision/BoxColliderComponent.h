#pragma once

#include "ColliderComponent.h"
#include "Engine/GameTool/Utility/Geometry/Box.h"

/*
BoxColliderComponent represents an axis-aligned bounding box (AABB) collider.
It handles collision detection using box geometry and provides debug rendering.
 */
class BoxColliderComponent : public ColliderComponent
{
public:
	/*
	 * Constructor for BoxColliderComponent.
	 * @param pOwner The actor that owns this collider component.
	 * @param pBox The local-space box geometry for the collider (default: empty box).
	 */
	BoxColliderComponent(Actor* pOwner, Box pBox = {});

	/*
	 * Renders a wireframe box in the world for debugging purposes.
	 * @param pRenderer The renderer used to draw the debug geometry.
	 */
	void DebugRender(IRenderer* pRenderer) override;

	/*
	 * Checks for collision between this box collider and another collider.
	 * Only supports collision with other BoxColliderComponent instances.
	 * @param pComponent Pointer to the other collider component.
	 * @return True if a collision is detected, false otherwise.
	 */
	bool Collision(const ColliderComponent* pComponent) override;

	/*
	 * Gets the world-space representation of this box collider.
	 * Takes into account the owning actor's transform (position and scale).
	 * @return The world-space bounding box.
	 */
	Box GetWorldBox() const;

	Box mBox; // Local-space axis-aligned box defining the collider shape
};

