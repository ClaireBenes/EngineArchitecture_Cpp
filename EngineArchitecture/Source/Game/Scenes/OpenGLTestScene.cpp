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
    mFloorMesh->SetShaderProgram(RendererGL::mSandShaderProgram); //RendererGL::mSimpleMeshShaderProgram

    //Sand
    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/sand.png", "sandTex");
    mFloorMesh->AddTexture(AssetManager::GetTexture("sandTex"));

    //// ----- GRASS -----
    //AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/grass.png", "floor");
    //mFloorMesh->AddTexture(AssetManager::GetTexture("floor"));
    // 
    //mGrassMesh = AssetManager::LoadMesh("plant.obj", "grassBlade");
    //mGrassMesh->SetShaderProgram(RendererGL::mGrassShaderProgram);

    //AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/plant3.png", "plant");
    //mGrassMesh->AddTexture(AssetManager::GetTexture("plant"));
    //// ----- END GRASS -----

    // ----- SKY -----
    Mesh* skySphere = AssetManager::LoadMesh("sphere.obj", "sphere");
    skySphere->SetShaderProgram(RendererGL::mSimpleMeshShaderProgram);

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/sky.png", "skyTex");
    skySphere->AddTexture(AssetManager::GetTexture("skyTex"));
    // ----- END SKY -----

    // ----- Wave -----
    Mesh* waterMesh = AssetManager::LoadMesh("plane.obj", "plane");
    waterMesh->SetShaderProgram(RendererGL::mWaveShaderProgram);

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/voronoise.png", "waveTex");
    waterMesh->AddTexture(AssetManager::GetTexture("waveTex"));
    // ----- END WAVE -----
}

void OpenGLTestScene::Start()
{
    SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    Floor* floor = new Floor();
    floor->SetTextureTiling(2, 2);
    AddActor(floor);
    floor->mTransform->mScale = Vector3(11, 0.0f, 10);
    floor->mTransform->mPosition = { -0.6f + floor->mTransform->mScale.x, -2.5f, 11 };

    // ----- SKY -----
    Actor* sky = new Actor();
    sky->mTransform->mPosition = { 0, -250, 10 };
    sky->mTransform->mScale = { 2000.0f, 2000.0f, 2000.0f };
    sky->mTransform->RotatePitch(180);

    MeshComponent* meshComponent = new MeshComponent(sky, AssetManager::GetMesh("sphere"));
    AddActor(sky);
    // ----- END SKY -----

    // ----- Wave -----
    Actor* waves = new Actor();
    waves->mTransform->mScale = Vector3(10, 1.0f, 10);
    waves->mTransform->mPosition = Vector3(-0.6f + floor->mTransform->mScale.x, -2, 15);
    MeshComponent* wavesMeshComponent = new MeshComponent(waves, AssetManager::GetMesh("plane"));
    AddActor(waves);
    waves->mTransform->RotateYaw(20);
    // ----- END WAVE -----

    // ----- GRASS -----
    //Grass* grass = new Grass();
    //AddActor(grass);
    //grass->mTransform->mPosition = { 0, -2.5f, 2 };
    // ----- END GRASS -----

    mCamera = new Camera();
    AddActor(mCamera);
    mCamera->mTransform->mPosition = { -0.6f + floor->mTransform->mScale.x , 0, 0};

    mMoveComponent = new EditorController(mCamera);
}

void OpenGLTestScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
}
