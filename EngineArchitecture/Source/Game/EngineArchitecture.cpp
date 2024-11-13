#include <iostream>

#include <SDL.h>
#include <glew.h>

#include "Engine/Engine.h"

#include "Pong.h"

int main(int argc, char* argv[])
{
	Engine pong ("Claire's Game Engine", { new Pong });

	return 0;
}



