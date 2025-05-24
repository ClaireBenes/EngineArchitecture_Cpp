#pragma once

#include <string>
#include <vector>

#include "SDL.h"

class IRenderer;
class Window;
class Actor;

/**
 * @brief Base class representing a game scene that manages actors and rendering.
 * Scenes handle actor lifecycles (add, update, remove) and are tied to a specific window and renderer.
 * Derived classes should override Load and Start to define behavior.
 */
class Scene
{
public:
	Scene();

	/**
	 * @brief Scene destructor.
	 * Cleans up all actors and clears loaded assets.
	 */
	virtual ~Scene();

	//Virtual functions

	/**
	 * @brief Called once before the scene starts. Override to load assets or initialize data.
	 */
	virtual void Load() {};

	/**
	 * @brief Called once after Load. Must be implemented to initialize gameplay logic.
	 */
	virtual void Start() = 0;

	/**
	 * @brief Updates all actors in the scene.
	 * Handles actor lifecycle: updates active ones, removes dead ones, and adds any newly pending actors.
	 * @param deltaTime Time elapsed since the last frame.
	 */
	virtual void Update(float deltaTime);

	//Non virtual functions

	/**
	 * @brief Sets the window associated with the scene.
	 * @param pWindow Pointer to the Window instance.
	 */
	void SetWindow(Window* pWindow);
	/**
	 * @brief Gets the window in which the scene in showing.
	 * @return Pointer to the Window instance used by the scene.
	 */
	Window* GetWindow();
	/**
	 * @brief Sets the renderer used by the scene.
	 * @param pRenderer Pointer to the IRenderer implementation.
	 */
	void SetRenderer(IRenderer* pRenderer);
	/**
	 * @brief Gets the renderer associated with the scene.
	 * @return Pointer to the IRenderer instance used by the scene.
	 */
	IRenderer* GetRenderer();

	/**
	 * @brief Reloads the scene.
	 * This is safe to call during an update since the operation happens at the end of an update.
	 */
	void Reload();

	/**
	 * @brief Adds a new actor to the scene.
	 * If called during actor updates, the addition is deferred until the update cycle ends.
	 * @param pActor Pointer to the actor to add.
	 */
	void AddActor(Actor* pActor);

	/**
	 * @brief Removes an actor from the scene, either from the active or pending actor lists.
	 * @param pActor Pointer to the actor to be removed.
	 *
	 * The function searches for the actor in both `mPendingActors` and `mActors`,
	 * swaps it with the last element if found, and then removes it from the list.
	 * This avoids invalidating iterators and ensures efficient removal.
	 */
	void RemoveActor(Actor* pActor);

protected:
	/**
	 * @brief Pointer to the window the scene uses
	 */
	Window* mWindow; 
	/**
	 * @brief Renderer responsible for drawing
	 */ 
	IRenderer* mRenderer; 
	/**
	 * @brief List of currently active actors
	 */
	std::vector<Actor*> mActors{}; 

private:
	/**
	 * @brief Actors to be added after the current update loop (deferred to avoid modifying mActors mid-iteration)
	 */
	std::vector<Actor*> mPendingActors {}; 
	/**
	 * @brief Actors marked for deletion after update
	 */
	std::vector<Actor*> mActorsToDelete {}; 

	/**
	 * @brief Flag to prevent actor list modification during update
	 */ 
	bool mIsUpdatingActors = false;	
	bool mShouldReload = false;
};

