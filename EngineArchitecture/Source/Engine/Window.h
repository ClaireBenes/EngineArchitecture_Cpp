#pragma once
#include "SDL.h"

#include "Log.h"
#include "Engine/GameTool/Utility/Vector/Vector2.h"

/**
 * @brief The Window class encapsulates an SDL window used for rendering the game.
 * It handles window creation, access to window dimensions, and cleanup.
 */
class Window
{
public:
	/**
	 * @brief Constructs a Window with specified width, height, and title.
	 * @param pWidth Width of the window in pixels.
	 * @param pHeight Height of the window in pixels.
	 * @param pTitle Title text for the window.
	 */
	Window(int pWidth, int pHeight, std::string pTitle);

	// Deleted copy constructor and assignment operator to prevent copies
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	/**
	 * @brief Gets the dimensions of the window.
	 * @return A Vector2 representing the window's width and height.
	 */
	Vector2 GetDimensions() const;
	/**
	 * @brief Gets the raw SDL_Window pointer.
	 * @return Pointer to the internal SDL_Window.
	 */
	SDL_Window* GetSdlWindow() const;

	/**
	 * @brief Initializes the SDL video subsystem and creates the window.
	 * @return True if the window was created successfully, false otherwise.
	 */
	bool Open();
	/**
	 * @brief Updates the window per frame (currently unused).
	 */
	void Update();
	/**
	 * @brief Closes and destroys the SDL window.
	 */
	void Close();

private:
	/**
	 * @brief Window dimensions in pixels
	 */
	Vector2 mDimensions = { 0,0 };
	/**
	 * @brief Pointer to the SDL window
	 */
	SDL_Window* mSdlWindow;
	/**
	 * @brief Title displayed in the window
	 */
	std::string mTitle = "Best Game";
};

