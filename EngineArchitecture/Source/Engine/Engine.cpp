#include "Engine.h"

Engine::Engine(std::string pTitle, std::vector<Scene*> pScene) : mScenes(pScene), mIsRunning(true)
{
    //initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
    }
    else
    {
        std::cout << "SDL initialization succeeded!\n";
    }

    mTitle = pTitle;

    Initialize();
}

void Engine::Initialize()
{
    //Create Window and Renderer
    mWindow = new Window(800, 800, mTitle);
    mRenderer = new Renderer();

    //if we have at least one scene -> Start it
    if(mScenes.size() > 0)
    {
        mScenes[mLoadedScene]->SetWindow(mWindow);
        mScenes[mLoadedScene]->Start(mRenderer);
    }

    //Go into main game loop when initialize is finished
    if(mWindow->Open() && mRenderer->Initialize(*mWindow))
    {
        Loop();
    }
}

//Main game loop
void Engine::Loop()
{
    while(mIsRunning)
    {
        Time::ComputeDeltaTime();

        Update();
        CheckForInputs();
        Render();

        Time::DelayTime();
    }
    Close();
}

//Draw
void Engine::Render()
{
    mRenderer->BeginDraw();
    mScenes[mLoadedScene]->Render();

    mRenderer->EndDraw();
}

//Update
void Engine::Update()
{
    mScenes[mLoadedScene]->Update(Time::deltaTime);
}

//Input Handler
void Engine::CheckForInputs()
{
    if(mIsRunning)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                //Quit game
                case SDL_QUIT:
                    mIsRunning = false;
                    break;
                case SDL_KEYDOWN :
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        mIsRunning = false;
                    }
                default:
                    break;
            }

            //check input of specific scene
            mScenes[mLoadedScene]->OnInput(event);
        }
    }

}

//Close game
void Engine::Close()
{
    mScenes[mLoadedScene]->Close();
    SDL_Quit();
}
