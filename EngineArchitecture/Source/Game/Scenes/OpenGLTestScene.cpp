#include "OpenGLTestScene.h"

#include "Engine/Engine.h"
#include "Engine/Renderer/RendererGL.h"
#include "Engine/Manager/AssetManager.h"

#include "Engine/GameTool/Movement/Controller/EditorController.h"
#include "Engine/GameTool/Camera.h"
#include "Game/Actors/Floor.h"
#include "Game/Actors/Grass.h"

void OpenGLTestScene::Load()
{
    mFloorMesh = AssetManager::LoadMesh("plane.obj", "cube");
    mFloorMesh->SetShaderProgram(RendererGL::mSimpleMeshShaderProgram);

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/grass.png", "floor");
    mFloorMesh->AddTexture(AssetManager::GetTexture("floor"));

    mGrassMesh = AssetManager::LoadMesh("grassBlade.obj", "grassBlade");
    mGrassMesh->SetShaderProgram(RendererGL::mGrassShaderProgram);
    mGrassMesh->AddTexture(AssetManager::GetTexture("floor"));
}

void OpenGLTestScene::Start()
{
    SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    Floor* floor = new Floor();
    AddActor(floor);
    floor->mTransform->mScale = Vector3(10, 0.0f, 10);
    floor->mTransform->mPosition = { 0, -2.5f, 10 };

    Grass* grass = new Grass();
    AddActor(grass);
    grass->mTransform->mPosition = { 0, -2.5f, 10 };

    mCamera = new Camera();
    AddActor(mCamera);

    mMoveComponent = new EditorController(mCamera);
}

void OpenGLTestScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
}

void OpenGLTestScene::Render()
{
    Scene::Render();
}
