#include <iostream>

#include <SDL.h>
#include <glew.h>

#include "Vector2.h"
#include "Log.h"
#include "Game.h"
#include "Pong.h"

int main(int argc, char* argv[])
{
	Game pong ("Claire's Game Engine", { new Pong });
	pong.Initialize();

	return 0;
}



