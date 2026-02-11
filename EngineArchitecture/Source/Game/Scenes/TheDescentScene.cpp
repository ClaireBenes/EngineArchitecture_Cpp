#include "TheDescentScene.h"

#include "Engine/Engine.h"
#include "Engine/Renderer/RendererGL.h"
#include "Engine/Manager/AssetManager.h"

#include "Engine/GameTool/Movement/Controller/EditorController.h"
#include "Engine/GameTool/Visual/Render/Sprite/SpriteRenderComponent.h"
#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"
#include "Engine/GameTool/Camera.h"

#include "Game/Actors/Floor.h"
#include "Game/Actors/TheDescent/TheDescentPlayer.h"
#include "Game/Actors/TheDescent/SimpleEnemy.h"

void TheDescentScene::Load()
{
    //Floor
    Mesh* floorMesh = AssetManager::LoadMesh("underwater.obj", "cube");
    floorMesh->SetShaderProgram(RendererGL::mSimpleMeshShaderProgram);

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/pilars.png", "floor");
    floorMesh->AddTexture(AssetManager::GetTexture("floor"));

    // ----- SKY -----
    Mesh* skySphere = AssetManager::LoadMesh("sphere.obj", "sphere");
    skySphere->SetShaderProgram(RendererGL::mSimpleMeshShaderProgram);

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/underwaterSkybox.jpeg", "skyTex");
    skySphere->AddTexture(AssetManager::GetTexture("skyTex"));
    // ----- END SKY -----

    //Projectile
    Mesh* projectileMesh = AssetManager::LoadMesh("sphere.obj", "caillou");
    projectileMesh->SetShaderProgram(RendererGL::mSimpleMeshShaderProgram);

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/bubble.png", "rockTex");
    projectileMesh->AddTexture(AssetManager::GetTexture("rockTex"));

    //Enemy
    Mesh* jellfish = AssetManager::LoadMesh("jellfish.obj", "jellfish");
    jellfish->SetShaderProgram(RendererGL::mSimpleMeshShaderProgram);

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/bowlingBall.png", "jellyfish");
    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/bowlingBallHurt.png", "jellyfishHurt");
    jellfish->AddTexture(AssetManager::GetTexture("jellyfish"));
    jellfish->AddTexture(AssetManager::GetTexture("jellyfishHurt"));

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

    InitializeFloors();
    InitializeEnemies();

    mPlayer = new TheDescentPlayer();
    AddActor(mPlayer);
    mPlayer->mTransform->mPosition = { -50, -50, -10 };
}

void TheDescentScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
}

void TheDescentScene::InitializeFloors()
{
    // Middle
    Floor* floor = new Floor();
    floor->SetTextureTiling(0.8, 0.8);
    AddActor(floor);
    floor->mTransform->mScale = Vector3(0.05f, 0.05f, 0.05f);
    floor->mTransform->mPosition = { 0.0, -100.5f, 35 };

    // Front
    Floor* floor2 = new Floor();
    floor2->SetTextureTiling(0.8, 0.8);
    AddActor(floor2);
    floor2->mTransform->mScale = Vector3(0.05f, 0.05f, 0.05f);
    floor2->mTransform->mPosition = { 200.0, -100.5f, 35 };

    // Behind
    Floor* floor3 = new Floor();
    floor3->SetTextureTiling(0.8, 0.8);
    AddActor(floor3);
    floor3->mTransform->mScale = Vector3(0.05f, 0.05f, 0.05f);
    floor3->mTransform->mPosition = { -200.0, -100.5f, 35 };

    // Left
    Floor* floor4 = new Floor();
    floor4->SetTextureTiling(0.8, 0.8);
    AddActor(floor4);
    floor4->mTransform->mScale = Vector3(0.05f, 0.05f, 0.05f);
    floor4->mTransform->mPosition = { 0.0, -100.5f, 235 };

    // Right
    Floor* floor5 = new Floor();
    floor5->SetTextureTiling(0.8, 0.8);
    AddActor(floor5);
    floor5->mTransform->mScale = Vector3(0.05f, 0.05f, 0.05f);
    floor5->mTransform->mPosition = { 0.0, -100.5f, -165 };

    // Diagonal Left Front
    Floor* floor6 = new Floor();
    floor6->SetTextureTiling(0.8, 0.8);
    AddActor(floor6);
    floor6->mTransform->mScale = Vector3(0.05f, 0.05f, 0.05f);
    floor6->mTransform->mPosition = { 200.0, -100.5f, 235 };

    // Diagonal Right Front
    Floor* floor7 = new Floor();
    floor7->SetTextureTiling(0.8, 0.8);
    AddActor(floor7);
    floor7->mTransform->mScale = Vector3(0.05f, 0.05f, 0.05f);
    floor7->mTransform->mPosition = { 200.0, -100.5f, -165 };

    // Diagonal Left Behind
    Floor* floor8 = new Floor();
    floor8->SetTextureTiling(0.8, 0.8);
    AddActor(floor8);
    floor8->mTransform->mScale = Vector3(0.05f, 0.05f, 0.05f);
    floor8->mTransform->mPosition = { -200.0, -100.5f, 235 };

    // Diagonal Right Behind
    Floor* floor9 = new Floor();
    floor9->SetTextureTiling(0.8, 0.8);
    AddActor(floor9);
    floor9->mTransform->mScale = Vector3(0.05f, 0.05f, 0.05f);
    floor9->mTransform->mPosition = { -200.0, -100.5f, -165 };
}

void TheDescentScene::InitializeEnemies()
{
    srand(time(0));
    int randomNum = rand() % 181;

    SimpleEnemy* enemy = new SimpleEnemy();
    enemy->mTransform->mPosition = { 10, -10, 10 };
    AddActor(enemy);
    enemy->mTransform->mScale *= 0.5;
    enemy->mTransform->RotateYaw(randomNum);


    SimpleEnemy* enemy2 = new SimpleEnemy();
    enemy2->mTransform->mPosition = { -100, -50, 100 };
    AddActor(enemy2);
    enemy2->mTransform->RotateYaw(randomNum);


    SimpleEnemy* enemy3 = new SimpleEnemy();
    enemy3->mTransform->mPosition = { -200, -10, 50 };
    AddActor(enemy3);
    enemy3->mTransform->mScale *= 0.9;
    enemy3->mTransform->RotateYaw(randomNum);


    SimpleEnemy* enemy4 = new SimpleEnemy();
    enemy4->mTransform->mPosition = { 200, -10, 50 };
    AddActor(enemy4);
    enemy4->mTransform->RotateYaw(randomNum);


    SimpleEnemy* enemy5 = new SimpleEnemy();
    enemy5->mTransform->mPosition = { 150, -60, -50 };
    AddActor(enemy5);
    enemy5->mTransform->mScale *= 0.7;
    enemy5->mTransform->RotateYaw(randomNum);

    SimpleEnemy* enemy6 = new SimpleEnemy();
    enemy6->mTransform->mPosition = { 150, -20, 200 };
    AddActor(enemy6);
    enemy6->mTransform->RotateYaw(randomNum);
}
