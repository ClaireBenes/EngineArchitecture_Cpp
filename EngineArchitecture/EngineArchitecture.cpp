#include <iostream>

#include <SDL.h>
#include <glew.h>

#include "Vector2.h"
#include "Log.h"
#include "Game.h"
#include "Pong.h"
#include "Vector4.h"

int main(int argc, char* argv[])
{

	//Color c {4,4,4,4};
	Game pong ("Claire's Game Engine", { new Pong });
	pong.Initialize();

	return 0;
}



