#include "Game.h"

Game::Game(std::string pTitle, std::vector<Scene*> pScene) : mScenes(pScene), mIsRunning(true)
{
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
    mWindow = new Window(800, 800);
    mRenderer = new Renderer();

    if(mScenes.size() > 0)
    {
        mScenes[mLoadedScene]->SetWindow(mWindow);
        mScenes[mLoadedScene]->Start(mRenderer);
    }

    if(mWindow->Open() && mRenderer->Initialize(*mWindow))
    {
        Loop();
    }
}

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

void Game::Render()
{
    mRenderer->BeginDraw();
    mScenes[mLoadedScene]->Render();

    mRenderer->EndDraw();
}

void Game::Update()
{
    mScenes[mLoadedScene]->Update(Time::deltaTime);
}

void Game::CheckForInputs()
{
    if(mIsRunning)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    mIsRunning = false;
                    break;
                default:
                    //Send input to scene
                    break;
            }

            mScenes[mLoadedScene]->OnInput(event);
        }
    }

}

void Game::Close()
{
    mScenes[mLoadedScene]->Close();
    SDL_Quit();
}
