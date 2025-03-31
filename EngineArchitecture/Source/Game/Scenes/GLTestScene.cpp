#include "GLTestScene.h"

#include "Engine/GameTool/Visual/Mesh/Mesh.h"
#include "Engine/Renderer/RendererGL.h"
#include "Engine/Manager/AssetManager.h"

#include "Game/Actors/Pin.h"
#include "Game/Actors/Floor.h"
#include "Game/Actors/BowlingBall.h"

#include "Game/Actors/Bush.h"

void GLTestScene::Load()
{
    //Pin
    mPinMesh = AssetManager::LoadMesh("pin.obj", "pin");
    mPinMesh->SetShaderProgram(RendererGL::GetMeshShaderProgram());

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/pin.png", "pin");
    mPinMesh->AddTexture(AssetManager::GetTexture("pin"));

    //Floor
    mFloorMesh = AssetManager::LoadMesh("cube.obj", "cube");
    mFloorMesh->SetShaderProgram(RendererGL::GetMeshShaderProgram());

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/bowling.png", "floor");
    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/bowlingWall.jpg", "wall");
    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/back.jpg", "back");
    mFloorMesh->AddTexture(AssetManager::GetTexture("floor"));
    mFloorMesh->AddTexture(AssetManager::GetTexture("wall"));
    mFloorMesh->AddTexture(AssetManager::GetTexture("back"));

    mBall = AssetManager::LoadMesh("sphere.obj", "ball");
    mBall->SetShaderProgram(RendererGL::GetMeshShaderProgram());

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/bowlingBall.png", "ballTex");
    mBall->AddTexture(AssetManager::GetTexture("ballTex"));
}

void GLTestScene::Start()
{
	SDL_SetRelativeMouseMode(SDL_TRUE);

	mCamera = new Camera();
	AddActor(mCamera);
	mCamera->mTransform->mPosition = { 0, 10, -35 };

	Floor* floor = new Floor();
	AddActor(floor);
	floor->mTransform->mPosition = { 0, 15, -10 };

    Floor* leftWall = new Floor();
    leftWall->SetTextureIndex(1);
    AddActor(leftWall);
    leftWall->mTransform->mScale = { 5, 5, 20 };
    leftWall->mTransform->mPosition = { 10, 10, -10 };

    Floor* rightWall = new Floor();
    rightWall->SetTextureIndex(1);
    AddActor(rightWall);
    rightWall->mTransform->mScale = leftWall->mTransform->mScale;
    rightWall->mTransform->mPosition = { -10, 10, -10 };

    Floor* ceiling = new Floor();
    ceiling->SetTextureIndex(1);
    AddActor(ceiling);
    ceiling->mTransform->mPosition = { 0, 4, -10 };

    Floor* back = new Floor();
    back->SetTextureIndex(1);
    AddActor(back);
    back->mTransform->mScale = { 5, 5, 2 };
    back->mTransform->mPosition = { 0, 10, 10 };

    //Pins
    for (int i = 0, row = 0, rowStart = 0; i < 10; i++)
    {
        int rows[] = {4, 3, 2, 1 };  // Pins per row
        while (i >= rowStart + rows[row])  // Determine current row
        {
            rowStart += rows[row];
            row++;
        }

        int count = rows[row];  // Pins in the current row
        float x = (i - rowStart) - (count - 1) / 2.0f; // Center the row
        float z = static_cast<float>(row) * -1.5f;  // Push row forward

        Pin* pin = new Pin();
        pin->mTransform->mPosition = { x * 1.5f, 13.5, z };
        AddActor(pin);
    }

    BowlingBall* ball = new BowlingBall();
    AddActor(ball);
    ball->mTransform->mPosition = { 0, 10, -30 };
}

void GLTestScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);

    //change camera placement
    mCameraDelay -= deltaTime;
    if (mCameraDelay <= 0.0f && !mCameraHasMoved)
    {
        mCamera->mTransform->mPosition = { 0, 3, -9 };
        mCamera->mTransform->RotatePitch(-40);
        mCameraHasMoved = true;
    }
}

void GLTestScene::Render()
{
	Scene::Render();
}
