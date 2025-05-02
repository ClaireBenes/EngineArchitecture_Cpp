#include "Doom.h"

#include "Engine/Engine.h"
#include "Engine/Renderer/RendererGL.h"
#include "Engine/Manager/AssetManager.h"

#include "Game/Actors/Floor.h"
#include "Game/Actors/Doom/DoomPlayer.h"
#include "Game/Actors/Doom/FirstEnemy.h"
#include "Game/Actors/Grass.h"

#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"

void Doom::Load()
{
    //Floor
    mFloorMesh = AssetManager::LoadMesh("cube.obj", "cube");
    mFloorMesh->SetShaderProgram(RendererGL::mSimpleMeshShaderProgram);

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/grass.png", "floor");
    mFloorMesh->AddTexture(AssetManager::GetTexture("floor"));

    //FirstEnemy
    mFirstEnemy = AssetManager::LoadMesh("plane.obj", "plane");
    mFirstEnemy->SetShaderProgram(RendererGL::mSimpleMeshShaderProgram);

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/coco.png", "coco");
    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/CocoHurt.png", "cocoHurt");
    mFirstEnemy->AddTexture(AssetManager::GetTexture("coco"));
    mFirstEnemy->AddTexture(AssetManager::GetTexture("cocoHurt"));

    //Caillou
    Mesh* projectileMesh = AssetManager::LoadMesh("stone.obj", "caillou");
    projectileMesh->SetShaderProgram(RendererGL::mSimpleMeshShaderProgram);

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/stone.png", "rock");
    projectileMesh->AddTexture(AssetManager::GetTexture("rock"));

    //Gyroid
    Mesh* enemyProjectileMesh = AssetManager::LoadMesh("gyroid.obj", "gyroid");
    enemyProjectileMesh->SetShaderProgram(RendererGL::mSimpleMeshShaderProgram);

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/Gyroid.png", "gyroidTex");
    enemyProjectileMesh->AddTexture(AssetManager::GetTexture("gyroidTex"));

    //Sky
    Mesh* skySphere = AssetManager::LoadMesh("sphere.obj", "sphere");
    skySphere->SetShaderProgram(RendererGL::mSimpleMeshShaderProgram);

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/sky.png", "skyTex");
    skySphere->AddTexture(AssetManager::GetTexture("skyTex"));
}

void Doom::Start()
{
    SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    Actor* sky = new Actor();
    sky->mTransform->mPosition = { 0, -250, 10 };
    sky->mTransform->mScale = { 2000.0f, 2000.0f, 2000.0f };
    sky->mTransform->RotatePitch(180);

    MeshComponent* meshComponent = new MeshComponent(sky, AssetManager::GetMesh("sphere"));
    AddActor(sky);

    Floor* floor = new Floor();
    AddActor(floor);
    floor->mTransform->mScale = Vector3(50, 0.01f, 50);
    floor->mTransform->mPosition = { 0, -2.5f, 10 };

    mPlayer = new DoomPlayer();
    AddActor(mPlayer);
    mPlayer->mTransform->mPosition = { 0, 1.8f, 0 };

    FirstEnemy* firstEnemy = new FirstEnemy();
    firstEnemy->mTransform->mPosition = { 0, 0, 10 };
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
