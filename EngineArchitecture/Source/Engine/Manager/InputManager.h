#pragma once
#include <map>
#include "Engine/GameTool/Movement/Input/InputEvent.h"

/**
 * @brief Overload of the comparison operator for SDL_MouseButtonEvent to enable usage in a map.
 * @param mb1 The first mouse button event.
 * @param mb2 The second mouse button event.
 * @return True if the type of mb1 is less than mb2.
 */
static bool operator<(const SDL_MouseButtonEvent& mb1, const SDL_MouseButtonEvent& mb2) { return mb1.type < mb2.type; }

/**
 * @brief The InputManager class is responsible for handling user input events, including keyboard and mouse input.
 * It allows subscribers to register for specific input events (key presses and mouse button events) 
 * and notifies them when the events occur.
 */
class InputManager
{
	/**
	 * @brief Map for storing keyboard events (key code -> InputEvent).
	 */
	std::map<SDL_Keycode, InputEvent*> mInputEvents;
	/**
	 * @brief Map for storing mouse events (mouse button -> InputEvent).
	 */
	std::map<Uint32, InputEvent*> mMouseEvents;

public:
	// Constructor and destructor.
	InputManager() = default;
	~InputManager();

	// Deleted copy constructor and assignment operator to prevent duplication.
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	/**
	 * @brief Returns the singleton instance of the InputManager.
	 * @return Reference to the static InputManager instance.
	 */
	static InputManager& Instance();

	/**
	 * @brief Handles input events (key and mouse events) and notifies the corresponding listeners.
	 * @param pEvent The SDL event to be processed.
	 */
	void HandleInputs(SDL_Event& pEvent);
	/**
	 * @brief Subscribes a listener to a specific keyboard key event.
	 * @param pKeyCode The SDL keycode for the key to subscribe to.
	 * @param pListener The listener that will be notified when the key event occurs.
	 */
	void SubscribeToKey(SDL_Keycode pKeyCode, IInputListener* pListener);
	/**
	 * @brief Subscribes a listener to a specific mouse button event.
	 * @param pButton The SDL mouse button to subscribe to (e.g., SDL_BUTTON_LEFT).
	 * @param pListener The listener that will be notified when the mouse button event occurs.
	 */
	void SubscribeToMouse(Uint8 pButton, IInputListener* pListener);
	/**
	 * @brief Unsubscribes from a listener
	 * @param pListener The listener that we want to unsubscribe of.
	 */
	void UnSubscribeToAllEvents(IInputListener* pListener);
};

