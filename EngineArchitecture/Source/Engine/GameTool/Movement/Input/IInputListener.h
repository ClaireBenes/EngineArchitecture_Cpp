#pragma once
#include "SDL_events.h"

/*
 * Interface for classes that want to receive input events.
 * Classes implementing this interface must handle SDL_Event notifications.
 */
class IInputListener
{
public:
	virtual ~IInputListener() = default;

	/*
	 * Called when an input event occurs.
	 * @param pEvent Reference to the SDL_Event received from the input system.
	 */
	virtual void OnNotify(SDL_Event& pEvent) = 0;
};

