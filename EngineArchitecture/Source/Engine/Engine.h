#pragma once

#include <string>
#include <vector>

#include "Window.h"
#include "Engine/Renderer/IRenderer.h"
#include "GameTool/Scene.h"
#include "Time.h"
#include "GameTool/Utility/Vector/Vector2.h"

/*
Engine is the main class responsible for initializing and running the game.
It manages the game loop, rendering, updating the game world, handling input, and managing scenes. 
The Engine class interacts with the renderer, window, and various game components, 
ensuring that the game runs efficiently and responds to user input.
*/
class Engine
{
public:
	/*
	Constructor for Engine.
	Initializes the engine with a window title, a list of scenes, and a specified renderer type.
	@param pTitle The title of the window.
	@param pScene A vector of pointers to Scene objects.
	@param pRendererType The type of renderer to use (e.g., SDL, OpenGL).
	*/
	Engine(std::string pTitle, std::vector<Scene*> pScene, IRenderer::RendererType pRendererType);
	/*
	Destructor for Engine.
	Cleans up the renderer, window, and scenes.
	*/
	~Engine();

	// Deleted copy constructor and assignment operator to prevent copying
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	/*
	Initializes the engine components, including the window, renderer, and first scene.
	@param pRendererType The type of renderer to use.
	*/
	void Initialize(IRenderer::RendererType pRendererType);
	/*
	Starts the main game loop. This function repeatedly updates the game state,
	processes input, and renders the game until the game is closed.
	*/
	void Loop();
	/*
	Renders the game by calling the renderer to draw all objects to the screen.
	*/
	void Render();
	/*
	Updates the game state by calling the current scene's update function.
	*/
	void Update();
	/*
	Checks for input events such as keyboard and window events, and processes them.
	*/
	void CheckForInputs();
	/*
	Closes the engine, performing necessary cleanup tasks.
	*/
	void Close();

public:
	// Static flags for debug and wireframe modes
	static inline bool mInDebugMode = false;
	static inline bool mInWireframeMode = false;
	static inline bool mIsGamePaused = false;

private:
	std::string mTitle = "The Title"; // The window title.
	std::vector<Scene*> mScenes{}; // The list of scenes managed by the engine.
	Window* mWindow{}; // The window for rendering.
	IRenderer* mRenderer{}; // The renderer used for drawing.

	bool mIsRunning = true; // Flag to indicate if the engine is running.
	int mLoadedScene = 0; // Index of the currently loaded scene.
};

