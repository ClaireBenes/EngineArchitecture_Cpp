#include <iostream>

#include <SDL.h>
#include <glew.h>

#include "Engine/Engine.h"

#include "Scenes/Pong.h"
#include "Scenes/SpaceInvaders.h"

int main(int argc, char* argv[])
{
	//Engine pong ("Claire's Game Engine", { new Pong });
	Engine spaceInvaders("Claire wants to destroy smt", { new SpaceInvaders });

	return 0;
}



