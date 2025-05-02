#pragma once

#include <string>
#include <vector>

#include "SDL.h"

class IRenderer;
class Window;
class Actor;

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
	void SetWindow(Window* pWindow);
	void SetRenderer(IRenderer* pRenderer);
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
	//Variables
	Window* mWindow;
	IRenderer* mRenderer;
	std::vector<Actor*> mActors{};

private:
	std::vector<Actor*> mPendingActors {};
	std::vector<Actor*> mActorsToDelete {};
	bool mIsUpdatingActors = false;
};

