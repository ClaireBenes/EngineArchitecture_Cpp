#pragma once
#include <map>
#include "Engine/GameTool/Movement/Input/InputEvent.h"

class InputManager
{
	std::map<SDL_Keycode, InputEvent*> mInputEvents;

public:
	InputManager() = default;
	~InputManager();
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	static InputManager& Instance();

	void HandleInputs(SDL_Event& pEvent);
	void SubscribeTo(SDL_Keycode pKeyCode, IInputListener* pListener);
};

