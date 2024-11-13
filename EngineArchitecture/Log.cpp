#include "Log.h"
#include <SDL_error.h>

//show message in console log
void Log::Info(const std::string& message)
{
	SDL_Log(message.c_str());
}

//show error
void Log::Error(LogType category, const std::string& message)
{
	SDL_LogError(static_cast< int >( category ), "%s | SDL : %s", message.c_str(), SDL_GetError());
}
