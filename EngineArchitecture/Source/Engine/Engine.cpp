#include "Engine.h"

#include "Manager/InputManager.h"

Engine::Engine(std::string pTitle, std::vector<Scene*> pScene) : mScenes(pScene), mIsRunning(true)
{
    //initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL initialization failed. SDL Error: %s\n", SDL_GetError());
    }
    else
    {
        printf("SDL initialization succeeded!\n");
    }

    mTitle = pTitle;

    Initialize();
}

Engine::~Engine()
{
    for(Scene* scene : mScenes)
    {
        delete scene;
    }

    delete mRenderer;
    delete mWindow;

    SDL_Quit();
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
        mScenes[mLoadedScene]->SetRenderer(mRenderer);
    }

    //Go into main game loop when initialize is finished
    if(mWindow->Open() && mRenderer->Initialize(*mWindow))
    {
        mScenes[mLoadedScene]->Load();
        mScenes[mLoadedScene]->Start();
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
                    InputManager::Instance().HandleInputs(event);
                    break;
            }
        }
    }
}
