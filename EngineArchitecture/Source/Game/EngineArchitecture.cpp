#include <iostream>

#include <SDL.h>
#include <glew.h>

#include "Engine/Engine.h"

#include "Scenes/Pong.h"
#include "Scenes/SpaceInvaders.h"
#include "Engine/Renderer/IRenderer.h"

int main(int argc, char* argv[])
{
	//Engine pong ("Claire's Game Engine", { new Pong });
	Engine spaceInvaders("Claire wants to destroy smt", { new SpaceInvaders },IRenderer::RendererType::OPENGL);

	return 0;
}



