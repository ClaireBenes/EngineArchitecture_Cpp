#pragma once
#include "SDL.h"

#include "Log.h"
#include "Engine/GameTool/Utility/Vector/Vector2.h"

/*
The Window class encapsulates an SDL window used for rendering the game.
It handles window creation, access to window dimensions, and cleanup.
*/
class Window
{
public:
	/*
	 * Constructs a Window with specified width, height, and title.
	 * @param pWidth Width of the window in pixels.
	 * @param pHeight Height of the window in pixels.
	 * @param pTitle Title text for the window.
	 */
	Window(int pWidth, int pHeight, std::string pTitle);

	// Deleted copy constructor and assignment operator to prevent copies
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	/*
	 * Gets the dimensions of the window.
	 * @return A Vector2 representing the window's width and height.
	 */
	Vector2 GetDimensions() const;
	/*
	 * Gets the raw SDL_Window pointer.
	 * @return Pointer to the internal SDL_Window.
	 */
	SDL_Window* GetSdlWindow() const;

	/*
	 * Initializes the SDL video subsystem and creates the window.
	 * @return True if the window was created successfully, false otherwise.
	 */
	bool Open();
	/*
	 Updates the window per frame (currently unused).
	 */
	void Update();
	/*
	 Closes and destroys the SDL window.
	 */
	void Close();

private:
	Vector2 mDimensions = { 0,0 }; // Window dimensions in pixels
	SDL_Window* mSdlWindow; // Pointer to the SDL window
	std::string mTitle = "Best Game"; // Title displayed in the window
};

