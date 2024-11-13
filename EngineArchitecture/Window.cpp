#include "Window.h"

Window::Window(int pWidth, int pHeight):mSdlWindow(nullptr), mDimensions({ static_cast<float>(pWidth), static_cast< float >(pHeight) })
{
}

//Get window dimensions
Vector2 Window::GetDimensions() const
{
	return mDimensions;
}

//Get SDL Window
SDL_Window* Window::GetSdlWindow() const
{
	return mSdlWindow;
}

bool Window::Open()
{
    //Create SDL Window
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        Log::Error(LogType::Video, "Unable to initialize video");
        return false;
    }

    mSdlWindow = SDL_CreateWindow("My Game", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        static_cast< int >( mDimensions.x ), 
        static_cast< int >( mDimensions.y),
        SDL_WINDOW_OPENGL );

    if(!mSdlWindow)
    {
        Log::Error(LogType::System, "Failed to create window");
        return false;
    }
    return true;

}

void Window::Update()
{
}

void Window::Close()
{
    SDL_DestroyWindow(mSdlWindow);
}
