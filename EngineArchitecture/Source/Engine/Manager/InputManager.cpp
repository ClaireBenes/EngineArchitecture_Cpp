#include "InputManager.h"

#include "Engine/Log.h"

InputManager::~InputManager()
{
	std::map<SDL_Keycode, InputEvent*>::iterator itKey;
	for (itKey = mInputEvents.begin(); itKey != mInputEvents.end(); itKey++)
	{
		delete ( itKey->second);
	}
	mInputEvents.clear();

	std::map<Uint32, InputEvent*>::iterator itMouse;
	for(itMouse = mMouseEvents.begin(); itMouse != mMouseEvents.end(); itMouse++)
	{
		delete ( itMouse->second );
	}
	mMouseEvents.clear();
}

InputManager& InputManager::Instance()
{
	static InputManager instance;
	return instance;
}

void InputManager::HandleInputs(SDL_Event& pEvent)
{

	std::map<SDL_Keycode, InputEvent*>::iterator itKey = mInputEvents.find(pEvent.key.keysym.sym);
	if (itKey != mInputEvents.end())
	{
		(*itKey ).second->NotifyListeners(pEvent);
	}

	std::map<Uint32, InputEvent*>::iterator itMouse = mMouseEvents.find(pEvent.button.type);

	if(itMouse != mMouseEvents.end())
	{
		( *itMouse ).second->NotifyListeners(pEvent);
	}
}

void InputManager::SubscribeToKey(SDL_Keycode pKeyCode, IInputListener* pListener)
{
	//The count function of map<T,U> returns 1 if the element exists, 0 otherwise
	size_t hasKey = mInputEvents.count(pKeyCode);
	if (hasKey == 0)
	{
		mInputEvents[pKeyCode] = new InputEvent();
	}
	mInputEvents[pKeyCode]->Subscribe(pListener);
}

void InputManager::SubscribeToMouse(SDL_MouseButtonEvent pKeyCode, IInputListener* pListener)
{
	//The count function of map<T,U> returns 1 if the element exists, 0 otherwise
	size_t hasKey = mMouseEvents.count(pKeyCode.type);

	//TODO : figure out how to bind the mouse (the subscribe type need to be at 1024)
	Log::Info("Subscribe to " + std::to_string(pKeyCode.type));

	if(hasKey == 0)
	{
		mMouseEvents[pKeyCode.type] = new InputEvent();
	}
	mMouseEvents[pKeyCode.type]->Subscribe(pListener);
}
