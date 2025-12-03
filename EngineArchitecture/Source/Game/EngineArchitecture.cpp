#include <iostream>

#include <SDL.h>
#include <glew.h>

#include "Engine/Engine.h"

#include "Scenes/Pong.h"
#include "Scenes/Platformer2D.h"
#include "Scenes/Bowling.h"
#include "Scenes/Doom.h"
#include "Scenes/OpenGLTestScene.h"
#include "Scenes/ComputeShader.h"

#include "Engine/Renderer/IRenderer.h"

/**
 * @mainpage Engine Documentation
 *
 * Welcome to the documentation for my **C++ Game Engine**!
 *
 * - Engine structure: see namespaces and architecture
 * - Game examples are excluded from this doc
 *
 * ---
 *
 * ### Quick Links
 * - [Classes](classes.html)
 * - [Namespaces](namespaces.html)
 * - [File List](files.html)
 */
int main(int argc, char* argv[])
{
	//Engine pong ("Claire's Game Engine", { new Pong }, IRenderer::RendererType::SDL);
	//Engine platformer("SDL 2D Platformer", { new Platformer2D },IRenderer::RendererType::SDL);
	//Engine bowling("OpenGL 3D Bowling", { new Bowling }, IRenderer::RendererType::OPENGL);
	//Engine doom("OpenGL 3D Not really Doom", { new Doom }, IRenderer::RendererType::OPENGL);

	Engine testScene("cloth", { new ComputeShader }, IRenderer::RendererType::OPENGL);

	return 0;
}