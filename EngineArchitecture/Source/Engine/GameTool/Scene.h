#pragma once

#include <string>
#include <vector>

#include "SDL.h"

class IRenderer;
class Window;
class Actor;

/*
 Base class representing a game scene that manages actors and rendering.
 Scenes handle actor lifecycles (add, update, remove) and are tied to a specific window and renderer.
 Derived classes should override Load and Start to define behavior.
 */
class Scene
{
public:
	Scene();

	/*
	 * Scene destructor.
	 * Cleans up all actors and clears loaded assets.
	 */
	virtual ~Scene();

	//Virtual functions

	/*
	 * Called once before the scene starts. Override to load assets or initialize data.
	 */
	virtual void Load() {};

	/*
	 * Called once after Load. Must be implemented to initialize gameplay logic.
	 */
	virtual void Start() = 0;

	/*
	 * Updates all actors in the scene.
	 * Handles actor lifecycle: updates active ones, removes dead ones, and adds any newly pending actors.
	 * @param deltaTime Time elapsed since the last frame.
	 */
	virtual void Update(float deltaTime);

	//Non virtual functions

	/*
	 * Sets the window associated with the scene.
	 * @param pWindow Pointer to the Window instance.
	 */
	void SetWindow(Window* pWindow);
	/*
	 * Sets the renderer used by the scene.
	 * @param pRenderer Pointer to the IRenderer implementation.
	 */
	void SetRenderer(IRenderer* pRenderer);
	/*
	 * Gets the renderer associated with the scene.
	 * @return Pointer to the IRenderer instance used by the scene.
	 */
	IRenderer* GetRenderer();

	/*
	 * Adds a new actor to the scene.
	 * If called during actor updates, the addition is deferred until the update cycle ends.
	 * @param pActor Pointer to the actor to add.
	 */
	void AddActor(Actor* pActor);

	/*
	 * Removes an actor from the scene, either from the active or pending actor lists.
	 * @param pActor Pointer to the actor to be removed.
	 *
	 * The function searches for the actor in both `mPendingActors` and `mActors`,
	 * swaps it with the last element if found, and then removes it from the list.
	 * This avoids invalidating iterators and ensures efficient removal.
	 */
	void RemoveActor(Actor* pActor);

protected:
	Window* mWindow; // Pointer to the window the scene uses
	IRenderer* mRenderer; // Renderer responsible for drawing
	std::vector<Actor*> mActors{}; // List of currently active actors

private:
	std::vector<Actor*> mPendingActors {}; // Actors to be added after the current update loop (deferred to avoid modifying mActors mid-iteration)
	std::vector<Actor*> mActorsToDelete {}; // Actors marked for deletion after update

	bool mIsUpdatingActors = false;	// Flag to prevent actor list modification during update
};

