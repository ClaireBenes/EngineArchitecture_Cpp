#pragma once
#include <map>
#include "Engine/GameTool/Movement/Input/InputEvent.h"

static bool operator<(const SDL_MouseButtonEvent& mb1, const SDL_MouseButtonEvent& mb2) { return mb1.type < mb2.type; }

class InputManager
{
	std::map<SDL_Keycode, InputEvent*> mInputEvents;
	std::map<Uint32, InputEvent*> mMouseEvents;

public:
	InputManager() = default;
	~InputManager();
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	static InputManager& Instance();

	void HandleInputs(SDL_Event& pEvent);
	void SubscribeToKey(SDL_Keycode pKeyCode, IInputListener* pListener);
	void SubscribeToMouse(Uint8 pButton, IInputListener* pListener);

};

