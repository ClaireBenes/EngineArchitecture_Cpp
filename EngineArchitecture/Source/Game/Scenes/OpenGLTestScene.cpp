#include "OpenGLTestScene.h"

#include "Engine/Engine.h"
#include "Engine/Renderer/RendererGL.h"
#include "Engine/Manager/AssetManager.h"

#include "Engine/GameTool/Movement/Controller/EditorController.h"
#include "Engine/GameTool/Camera.h"
#include "Game/Actors/Floor.h"
#include "Game/Actors/Grass.h"

#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"

void OpenGLTestScene::Load()
{
    mFloorMesh = AssetManager::LoadMesh("plane.obj", "cube");
    mFloorMesh->SetShaderProgram(RendererGL::mSimpleMeshShaderProgram);

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/grass.png", "floor");
    mFloorMesh->AddTexture(AssetManager::GetTexture("floor"));

    mGrassMesh = AssetManager::LoadMesh("plant.obj", "grassBlade");
    mGrassMesh->SetShaderProgram(RendererGL::mGrassShaderProgram);

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/plant3.png", "plant");
    mGrassMesh->AddTexture(AssetManager::GetTexture("plant"));

    //Sky
    Mesh* skySphere = AssetManager::LoadMesh("sphere.obj", "sphere");
    skySphere->SetShaderProgram(RendererGL::mSimpleMeshShaderProgram);

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/sky.png", "skyTex");
    skySphere->AddTexture(AssetManager::GetTexture("skyTex"));
}

void OpenGLTestScene::Start()
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
    floor->mTransform->mScale = Vector3(11, 0.0f, 10);
    floor->mTransform->mPosition = { -0.6f + floor->mTransform->mScale.x, -2.5f, 11 };

    Grass* grass = new Grass();
    AddActor(grass);
    grass->mTransform->mPosition = { 0, -2.5f, 2 };

    mCamera = new Camera();
    AddActor(mCamera);
    mCamera->mTransform->mPosition = { -0.6f + floor->mTransform->mScale.x , 0, 0};

    mMoveComponent = new EditorController(mCamera);
}

void OpenGLTestScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
}
