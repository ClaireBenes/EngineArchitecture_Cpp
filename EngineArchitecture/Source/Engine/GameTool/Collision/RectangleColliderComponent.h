#pragma once

#include "ColliderComponent.h"
#include "Engine/GameTool/Utility/Geometry/Rectangle.h"

/**
 * @brief RectangleColliderComponent represents a 2D axis-aligned bounding box (AABB) collider.
 * It provides collision detection and debug rendering for rectangular shapes in 2D space.
 */
class RectangleColliderComponent : public ColliderComponent
{
public:
    /**
     * @brief Constructor for RectangleColliderComponent.
     * @param pOwner The actor that owns this collider component.
     */
	RectangleColliderComponent(Actor* pOwner);

    /**
     * @brief Renders the rectangle as a line in the world for debugging purposes.
     * @param pRenderer The renderer used to draw the debug rectangle.
     */
	void DebugRender(IRenderer* pRenderer) override;

    /**
     * @brief Gets the world-space rectangle based on the owner's position.
     * Transforms the local-space rectangle to its global position.
     * @return A Rectangle in world-space coordinates.
     */
	Rectangle GetWorldRectangle() const;

    /**
     * @brief Checks for collision with another rectangle in world space.
     * @param otherRectangle The other rectangle to check against.
     * @return True if a collision is detected, false otherwise.
     */
	bool Collision(const Rectangle& otherRectangle);
    /**
     * @brief Checks for collision with another collider component.
     * Only supports collision with other RectangleColliderComponent instances.
     * @param pComponent Pointer to the other collider component.
     * @return True if a collision is detected, false otherwise.
     */
	bool Collision(const ColliderComponent* pComponent) override;

	Rectangle mRectangle{ Vector2(-16,-16),Vector2(32,32) };  // Local-space rectangle defining the collider shape
};

