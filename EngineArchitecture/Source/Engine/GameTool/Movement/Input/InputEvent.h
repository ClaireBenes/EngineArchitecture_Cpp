#pragma once

#include "SDL_events.h"

#include <vector>

class IInputListener;

class InputEvent
{
public:
	~InputEvent();

	void Subscribe(IInputListener* pListener);
	void Unsubscribe(IInputListener* pListener);

	void NotifyListeners(SDL_Event& pEvent) const;

private:
	std::vector<IInputListener*> mListeners;
};

