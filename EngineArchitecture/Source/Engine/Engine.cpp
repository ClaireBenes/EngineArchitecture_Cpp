#include "Engine.h"

#include "Manager/InputManager.h"
#include "Engine/Renderer/RendererSDL.h"
#include "Engine/Renderer/RendererGL.h"

Engine::Engine(std::string pTitle, std::vector<Scene*> pScene, IRenderer::RendererType pRendererType) : mScenes(pScene), mIsRunning(true)
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
    
    Initialize(pRendererType);
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

void Engine::Initialize(IRenderer::RendererType pRendererType)
{
    //Create Window
    mWindow = new Window(1280, 720, mTitle);

    //Create Renderer
    switch(pRendererType)
    {
        case IRenderer::RendererType::SDL:
            mRenderer = new RendererSDL();
            break;
        case IRenderer::RendererType::OPENGL:
            mRenderer = new RendererGL();
            break;
    }

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

        if (!mIsGamePaused) 
        {
            Update();
        }

        CheckForInputs();
        Render();

        Time::DelayTime();
    }
}

//Draw
void Engine::Render()
{
    mRenderer->BeginDraw();

    mRenderer->Draw();

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
            InputManager::Instance().HandleInputs(event);

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
                    if (event.key.keysym.sym == SDLK_p)
                    {
                        if (mInDebugMode) 
                        {
                            mInDebugMode = false;
                        }
                        else 
                        {
                            mInDebugMode = true;
                        }
                    }
                    if(event.key.keysym.sym == SDLK_w)
                    {
                        if(mInWireframeMode)
                        {
                            mInWireframeMode = false;
                        }
                        else
                        {
                            mInWireframeMode = true;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }
}
