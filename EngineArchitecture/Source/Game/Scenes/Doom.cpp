#include "Doom.h"

#include "Engine/Renderer/RendererGL.h"
#include "Engine/Manager/AssetManager.h"

#include "Game/Actors/Floor.h"
#include "Game/Actors/Doom/DoomPlayer.h"
#include "Game/Actors/Doom/FirstEnemy.h"

void Doom::Load()
{
    //Floor
    mFloorMesh = AssetManager::LoadMesh("cube.obj", "cube");
    mFloorMesh->SetShaderProgram(RendererGL::GetMeshShaderProgram());

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/grass.png", "floor");
    mFloorMesh->AddTexture(AssetManager::GetTexture("floor"));

    //FirstEnemy
    mFirstEnemy = AssetManager::LoadMesh("plane.obj", "plane");
    mFirstEnemy->SetShaderProgram(RendererGL::GetMeshShaderProgram());

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/Coco.png", "coco");
    mFirstEnemy->AddTexture(AssetManager::GetTexture("coco"));
}

void Doom::Start()
{
    SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    Floor* floor = new Floor();
    AddActor(floor);
    floor->mTransform->mScale = Vector3(5, 0.01f, 5);
    floor->mTransform->mPosition = { 0, -5, 10 };

    mPlayer = new DoomPlayer();
    AddActor(mPlayer);
    mPlayer->mTransform->mPosition = { 0, 0, 0 };

    FirstEnemy* firstEnemy = new FirstEnemy();
    firstEnemy->mTransform->mPosition = { 0, 1, 10 };
    firstEnemy->SetPlayer(mPlayer);
    AddActor(firstEnemy);
}

void Doom::Update(float deltaTime)
{
    Scene::Update(deltaTime);
}

void Doom::Render()
{
    Scene::Render();
}
