#pragma once

#include "SDL_events.h"

#include <vector>

class IInputListener;

/*
InputEvent is responsible for managing a list of input listeners and broadcasting SDL events to them.
Listeners can subscribe or unsubscribe to receive event notifications.
 */
class InputEvent
{
public:
	/*
	Destructor for InputEvent.
	Clears the list of subscribed listeners.
	 */
	~InputEvent();

	/*
	 * Subscribes a listener to receive SDL input events.
	 * @param pListener Pointer to the listener to be added.
	 */
	void Subscribe(IInputListener* pListener);
	/*
	 * Unsubscribes a listener so it no longer receives SDL input events.
	 * @param pListener Pointer to the listener to be removed.
	 */
	void Unsubscribe(IInputListener* pListener);

	/*
	 * Notifies all subscribed listeners of an SDL input event.
	 * @param pEvent Reference to the SDL_Event to broadcast.
	 */
	void NotifyListeners(SDL_Event& pEvent) const;

private:
	std::vector<IInputListener*> mListeners; // List of currently subscribed input listeners.
};

