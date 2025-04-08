#include "OpenGLTestScene.h"

#include "Engine/Engine.h"
#include "Engine/Renderer/RendererGL.h"
#include "Engine/Manager/AssetManager.h"

#include "Engine/GameTool/Movement/Controller/EditorController.h"
#include "Engine/GameTool/Camera.h"
#include "Game/Actors/Floor.h"

void OpenGLTestScene::Load()
{
    //Floor

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/HeightMap.png", "floor");

    mFloorMesh = AssetManager::LoadMesh("plane.obj", "cube");
    mFloorMesh->AddTexture(AssetManager::GetTexture("floor"));
    mFloorMesh->SetShaderProgram(RendererGL::mTesselationMeshShaderProgram);
}

void OpenGLTestScene::Start()
{
    SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    Floor* floor = new Floor();
    AddActor(floor);
    floor->mTransform->mScale = Vector3(10, 0.0f, 10);
    floor->mTransform->mPosition = { 0, -2.5f, 10 };

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
