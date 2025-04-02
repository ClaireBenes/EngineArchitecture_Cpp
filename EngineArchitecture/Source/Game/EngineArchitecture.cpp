#include <iostream>

#include <SDL.h>
#include <glew.h>

#include "Engine/Engine.h"

#include "Scenes/Pong.h"
#include "Scenes/Platformer2D.h"
#include "Scenes/Bowling.h"
#include "Scenes/Doom.h"

#include "Engine/Renderer/IRenderer.h"

int main(int argc, char* argv[])
{
	//Engine pong ("Claire's Game Engine", { new Pong }, IRenderer::RendererType::SDL);
	//Engine platformer("SDL 2D Platformer", { new Platformer2D },IRenderer::RendererType::SDL);
	//Engine bowling("OpenGL 3D Bowling", { new Bowling }, IRenderer::RendererType::OPENGL);
	Engine doom("OpenGL 3D Doom", { new Doom }, IRenderer::RendererType::OPENGL);

	return 0;
}