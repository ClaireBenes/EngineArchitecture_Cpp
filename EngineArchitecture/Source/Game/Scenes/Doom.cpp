#include "Doom.h"

#include "Engine/Engine.h"
#include "Engine/Renderer/RendererGL.h"
#include "Engine/Manager/AssetManager.h"
#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"

#include "Game/Actors/Floor.h"

#include "Game/Actors/Doom/DoomPlayer.h"
#include "Game/Actors/Doom/FirstEnemy.h"

#include "Game/Actors/Doom/HeartPickUp.h"
#include "Game/Actors/Doom/AmmoPickUp.h"
#include "Game/Actors/Doom/Door.h"
#include "Game/Actors/Doom/WinBox.h"


void Doom::Load()
{
    //Floor
    Mesh* floorMesh = AssetManager::LoadMesh("cube.obj", "cube");
    floorMesh->SetShaderProgram(RendererGL::mSimpleMeshShaderProgram);

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/grass.png", "floor");
    floorMesh->AddTexture(AssetManager::GetTexture("floor"));

    //Caillou
    Mesh* projectileMesh = AssetManager::LoadMesh("rock.obj", "caillou");
    projectileMesh->SetShaderProgram(RendererGL::mSimpleMeshShaderProgram);

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/Rock2.png", "rockHUD");
    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/Rock.png", "rock");
    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/stone.png", "rockTex");
    projectileMesh->AddTexture(AssetManager::GetTexture("rockTex"));

    //Plane (Enemy + heart Pick up + ammo pick up)
    Mesh* plane = AssetManager::LoadMesh("plane.obj", "plane");
    plane->SetShaderProgram(RendererGL::mSimpleMeshShaderProgram);

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/coco.png", "coco");
    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/CocoHurt.png", "cocoHurt");
    plane->AddTexture(AssetManager::GetTexture("coco"));
    plane->AddTexture(AssetManager::GetTexture("cocoHurt"));

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/Heart.png", "heart");
    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/Heart2.png", "heartHUD");
    plane->AddTexture(AssetManager::GetTexture("heart"));
    plane->AddTexture(AssetManager::GetTexture("rock"));

    //Gyroid
    Mesh* enemyProjectileMesh = AssetManager::LoadMesh("gyroid.obj", "gyroid");
    enemyProjectileMesh->SetShaderProgram(RendererGL::mSimpleMeshShaderProgram);

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/Gyroid2.png", "gyroidTex");
    enemyProjectileMesh->AddTexture(AssetManager::GetTexture("gyroidTex"));

    //BellBag
    Mesh* bellBagMesh = AssetManager::LoadMesh("bellBag.obj", "bellBag");
    bellBagMesh->SetShaderProgram(RendererGL::mSimpleMeshShaderProgram);

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/bellBag.png", "bellBagTex");
    bellBagMesh->AddTexture(AssetManager::GetTexture("bellBagTex"));

    //Door
    Mesh* doorMesh = AssetManager::LoadMesh("door.obj", "door");
    doorMesh->SetShaderProgram(RendererGL::mSimpleMeshShaderProgram);

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/door.png", "doorTex");
    doorMesh->AddTexture(AssetManager::GetTexture("doorTex"));

    //Sky
    Mesh* skySphere = AssetManager::LoadMesh("sphere.obj", "sphere");
    skySphere->SetShaderProgram(RendererGL::mSimpleMeshShaderProgram);

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/sky.png", "skyTex");
    skySphere->AddTexture(AssetManager::GetTexture("skyTex"));

    //UI
    //EndScreen
    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/WinScreen.png", "winScreenTex");
    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/LoseScreen.png", "loseScreen");

    //Cursor
    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/whiteOutlineCrosshair.png", "crosshair");

    //Lance Pierre
    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/lancePierre.png", "lance");
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

    mPlayer = new DoomPlayer();
    AddActor(mPlayer);
    mPlayer->mTransform->mPosition = { 0, 1.8f, 0 };

    InitializeFloors();

    Door* door = new Door();
    door->mTransform->mPosition = { -4.5f, -0.5f, 8.6f };
    door->SetPlayer(mPlayer);
    AddActor(door);

    Door* door2 = new Door();
    door2->mTransform->mPosition = { -4.5f, -0.5f, 37.6f };
    door2->SetPlayer(mPlayer);
    AddActor(door2);

    WinBox* winBox = new WinBox();
    winBox->mTransform->mPosition = { 1, -2.1f, 41 };
    winBox->SetPlayer(mPlayer);
    AddActor(winBox);

    InitializeEnemies();
    InitializePickUps();
}

void Doom::Update(float deltaTime)
{
    Scene::Update(deltaTime);
}

void Doom::InitializeFloors()
{
    Floor* floor = new Floor();
    AddActor(floor);
    floor->mTransform->mScale = Vector3(50, 0.01f, 50);
    floor->mTransform->mPosition = { 0, -2.5f, 35 };

    Floor* wall1 = new Floor();
    wall1->SetTextureTiling(20, 30);
    AddActor(wall1);
    wall1->mTransform->mScale = Vector3(5, 2, 0.5f);
    wall1->mTransform->mPosition = { 0, -0.5f, -5 };

    Floor* wall2 = new Floor();
    wall2->SetTextureTiling(20, 200);
    AddActor(wall2);
    wall2->mTransform->mScale = Vector3(0.5f, 2, 40);
    wall2->mTransform->mPosition = { -5, -0.5f, 35 };

    Floor* wall3 = new Floor();
    wall3->SetTextureTiling(20, 35);
    AddActor(wall3);
    wall3->mTransform->mScale = Vector3(0.5f, 2, 7);
    wall3->mTransform->mPosition = { 5, -0.5f, 2 };

    Floor* wall4 = new Floor();
    wall4->SetTextureTiling(20, 50);
    AddActor(wall4);
    wall4->mTransform->mScale = Vector3(10, 2, 0.5f);
    wall4->mTransform->mPosition = { 8.1f, -0.5f, 9 };

    Floor* wall5 = new Floor();
    wall5->SetTextureTiling(20, 100);
    AddActor(wall5);
    wall5->mTransform->mScale = Vector3(0.5f, 2, 20);
    wall5->mTransform->mPosition = { 18.1f, -0.5f, 18 };

    Floor* wall6 = new Floor();
    wall6->SetTextureTiling(20, 30);
    AddActor(wall6);
    wall6->mTransform->mScale = Vector3(5, 2, 0.5f);
    wall6->mTransform->mPosition = { 0, -0.5f, 25 };

    Floor* wall7 = new Floor();
    wall7->SetTextureTiling(20, 50);
    AddActor(wall7);
    wall7->mTransform->mScale = Vector3(10, 2, 0.5f);
    wall7->mTransform->mPosition = { 8.1f, -0.5f, 38 };

    Floor* wall8 = new Floor();
    wall8->SetTextureTiling(20, 30);
    AddActor(wall8);
    wall8->mTransform->mScale = Vector3(5, 2, 0.5f);
    wall8->mTransform->mPosition = { 0, -0.5f, 45 };

    Floor* wall9 = new Floor();
    wall9->SetTextureTiling(20, 30);
    AddActor(wall9);
    wall9->mTransform->mScale = Vector3(0.5f, 2, 5);
    wall9->mTransform->mPosition = { 4, -0.5f, 43 };
}

void Doom::InitializeEnemies()
{
    FirstEnemy* firstEnemy = new FirstEnemy();
    firstEnemy->mTransform->mPosition = { 2, 0, 23 };
    firstEnemy->SetPlayer(mPlayer);
    AddActor(firstEnemy);

    FirstEnemy* Enemy2 = new FirstEnemy();
    Enemy2->mTransform->mPosition = { 15, 0, 15 };
    Enemy2->SetPlayer(mPlayer);
    AddActor(Enemy2);

    FirstEnemy* Enemy3 = new FirstEnemy();
    Enemy3->mTransform->mPosition = { 10, 0, 35 };
    Enemy3->SetPlayer(mPlayer);
    AddActor(Enemy3);

    FirstEnemy* Enemy4 = new FirstEnemy();
    Enemy4->mTransform->mPosition = { -2, 0, 30 };
    Enemy4->SetPlayer(mPlayer);
    AddActor(Enemy4);
}

void Doom::InitializePickUps()
{
    // ---- AMMO ----
    AmmoPickUp* ammoPickUp = new AmmoPickUp();
    ammoPickUp->mTransform->mPosition = { -2.0f, -2.0f, 5.0f };
    ammoPickUp->SetPlayer(mPlayer);
    AddActor(ammoPickUp);

    AmmoPickUp* ammoPickUp3 = new AmmoPickUp();
    ammoPickUp3->mTransform->mPosition = { 15.0f, -2.0f, 20 };
    ammoPickUp3->SetPlayer(mPlayer);
    AddActor(ammoPickUp3);

    AmmoPickUp* ammoPickUp4 = new AmmoPickUp();
    ammoPickUp4->mTransform->mPosition = { 11, -2.0f, 30 };
    ammoPickUp4->SetPlayer(mPlayer);
    AddActor(ammoPickUp4);

    // ---- HEART ----
    HeartPickUp* heartPickUp = new HeartPickUp();
    heartPickUp->mTransform->mPosition = { -2.0f, -2.0f, 23 };
    heartPickUp->SetPlayer(mPlayer);
    AddActor(heartPickUp);

    HeartPickUp* heartPickUp2 = new HeartPickUp();
    heartPickUp2->mTransform->mPosition = { 8, -2.0f, 15 };
    heartPickUp2->SetPlayer(mPlayer);
    AddActor(heartPickUp2);

    HeartPickUp* heartPickUp3 = new HeartPickUp();
    heartPickUp3->mTransform->mPosition = { 8, -2.0f, 28 };
    heartPickUp3->SetPlayer(mPlayer);
    AddActor(heartPickUp3);

    // ---- AMMO ----
    AmmoPickUp* ammoPickUp2 = new AmmoPickUp();
    ammoPickUp2->mTransform->mPosition = { 5.0f, -2.0f, 23 };
    ammoPickUp2->SetPlayer(mPlayer);
    AddActor(ammoPickUp2);

    AmmoPickUp* ammoPickUp5 = new AmmoPickUp();
    ammoPickUp5->mTransform->mPosition = { 5.0f, -2.0f, 23 };
    ammoPickUp5->SetPlayer(mPlayer);
    AddActor(ammoPickUp5);
}
