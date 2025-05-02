#pragma once

#include "../Component.h"
#include "Engine/GameTool/Utility/Vector/Vector4.h"

#include "Engine/Renderer/DebugRenderInterface.h"

class IRendererSDL;

/*
Base class for collider components used in physics and collision detection.
Inherits from Component for lifecycle management and DebugRenderInterface for debug visualization.
 */
class ColliderComponent : public Component, public DebugRenderInterface
{
public:
	/*
	 * Constructor for ColliderComponent.
	 * @param pOwner The actor that owns this collider component.
	 */
	ColliderComponent(Actor* pOwner);

	/*
	Called when the component starts.
	Registers the component for debug rendering and adds it to the physics system.
	 */
	void OnStart() override;
	/*
	Called when the component ends.
	Unregisters the component from debug rendering and removes it from the physics system.
	 */
	void OnEnd() override;

	/*
	 * Pure virtual method to check collision with another collider component.
	 * Must be implemented by derived classes (e.g., BoxCollider, SphereCollider).
	 * @param pComponent Pointer to another collider component to check collision against.
	 * @return True if a collision is detected, false otherwise.
	 */
	virtual bool Collision(const ColliderComponent* pComponent) = 0;

	//Variables
	Color mColor{ 255,0,0,255 }; // Debug rendering color for the collider (default: red).
};

