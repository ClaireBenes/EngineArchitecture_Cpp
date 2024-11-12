#include <iostream>

#include <SDL.h>
#include <glew.h>

#include "Vector2.h"
#include "Log.h"
#include "Game.h"
#include "Pong.h"

using namespace std;

#define GLEW_STATIC

int main(int argc, char* argv[])
{
	Vector2 newVector = Vector2::ONE;
	newVector *= 2.0f;
	Log::Info(newVector.ToString());
	std::cin.get();

	Game* pong = new Game("Claire's Game Engine", { new Pong });
	pong->Initialize();

	return 0;
}



