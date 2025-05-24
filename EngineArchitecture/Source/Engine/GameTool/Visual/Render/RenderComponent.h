#pragma once

#include "Engine/GameTool/Component.h"
#include "Engine/GameTool/Utility/Vector/Vector4.h"

class IRenderer;

/**
 * @brief Defines different categories of rendering layers.
 * - World: 3D world space objects.
 * - Viewport: UI or overlay elements rendered in screen space.
 */
enum class RenderType
{
	World,
	Viewport
};

/**
 * @brief RenderComponent is an abstract base class for all components that need to be rendered.
 * It provides hooks for lifecycle events and defines the interface for rendering and draw order.
 */
class RenderComponent : public Component
{
public:
	/**
	 * @brief Constructs the RenderComponent and assigns it to the owning Actor.
	 * @param pOwner The Actor that owns this component.
	 */
	RenderComponent(Actor* pOwner);

	/**
	 * @brief Called when the component is started.
	 * Registers the component with the scene's renderer for drawing.
	 */
	void OnStart() override;
	/**
	 * @brief Called when the component is removed or destroyed.
	 * Unregisters the component from the renderer.
	 */
	void OnEnd() override;

	/**
	 * @brief Renders the component using the given renderer.
	 * Must be implemented by derived classes.
	 * @param rRenderer Reference to the renderer responsible for drawing.
	 */
	virtual void Render(IRenderer* rRenderer) = 0;
	/**
	 * @brief Returns the type of rendering this component belongs to (World or Viewport).
	 * Used for organizing rendering passes.
	 */
	virtual RenderType GetRenderType() = 0;
	/**
	 * @briefReturns the draw order priority of this component.
	 * Lower values are rendered first.
	 * Default is 0.
	 */
	virtual int GetDrawOrder() const;

	// Color used when rendering (default is white/opaque).
	Color mColor{ 255,255,255,255 };
};

