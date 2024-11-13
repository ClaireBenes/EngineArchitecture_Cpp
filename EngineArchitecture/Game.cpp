#include "Game.h"

Game::Game(std::string pTitle, std::vector<Scene*> pScene) : mScenes(pScene), mIsRunning(true)
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

    Initialize();
}

void Game::Initialize()
{
    //Create Window and Renderer
    mWindow = new Window(800, 800);
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
void Game::Loop()
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
void Game::Render()
{
    mRenderer->BeginDraw();
    mScenes[mLoadedScene]->Render();

    mRenderer->EndDraw();
}

//Update
void Game::Update()
{
    mScenes[mLoadedScene]->Update(Time::deltaTime);
}

//Input Handler
void Game::CheckForInputs()
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
void Game::Close()
{
    mScenes[mLoadedScene]->Close();
    SDL_Quit();
}
