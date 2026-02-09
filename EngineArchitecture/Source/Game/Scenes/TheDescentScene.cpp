#include "TheDescentScene.h"

#include "Engine/Engine.h"
#include "Engine/Renderer/RendererGL.h"
#include "Engine/Manager/AssetManager.h"

#include "Engine/GameTool/Movement/Controller/EditorController.h"
#include "Engine/GameTool/Camera.h"
#include "Engine/GameTool/Visual/Render/Sprite/SpriteRenderComponent.h"

#include "Game/Actors/Floor.h"
#include "Game/Actors/TheDescent/TheDescentPlayer.h"

#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"

void TheDescentScene::Load()
{
    //Floor
    Mesh* floorMesh = AssetManager::LoadMesh("cube.obj", "cube");
    floorMesh->SetShaderProgram(RendererGL::mSimpleMeshShaderProgram);

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/sand.png", "floor");
    floorMesh->AddTexture(AssetManager::GetTexture("floor"));

    // ----- SKY -----
    Mesh* skySphere = AssetManager::LoadMesh("sphere.obj", "sphere");
    skySphere->SetShaderProgram(RendererGL::mSimpleMeshShaderProgram);

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/underwater.png", "skyTex");
    skySphere->AddTexture(AssetManager::GetTexture("skyTex"));
    // ----- END SKY -----

    //UI
    //EndScreen
    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/WinScreen.png", "winScreenTex");
    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/LoseScreen.png", "loseScreen");

    //Cursor
    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/whiteOutlineCrosshair.png", "crosshair");

    //Cockpit
    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/cockpit.png", "cockpit");
}

void TheDescentScene::Start()
{
    SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    // ----- SKY -----
    Actor* sky = new Actor();
    sky->mTransform->mPosition = { 0, -250, 10 };
    sky->mTransform->mScale = { 2000.0f, 2000.0f, 2000.0f };
    sky->mTransform->RotatePitch(180);

    MeshComponent* meshComponent = new MeshComponent(sky, AssetManager::GetMesh("sphere"));
    AddActor(sky);
    // ----- END SKY -----

    Floor* floor = new Floor();
    AddActor(floor);
    floor->mTransform->mScale = Vector3(50, 0.01f, 50);
    floor->mTransform->mPosition = { 0, -2.5f, 35 };

    mPlayer = new TheDescentPlayer();
    AddActor(mPlayer);
    mPlayer->mTransform->mPosition = { 0, 1.8f, 0 };
}

void TheDescentScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
}
