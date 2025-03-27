#include "GLTestScene.h"

#include "Game/Actors/Pin.h"
#include "Game/Actors/Floor.h"

#include "Game/Actors/Bush.h"

void GLTestScene::Load()
{
}

void GLTestScene::Start()
{
	SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	mCamera = new Camera();
	AddActor(mCamera);
	mCamera->mTransform->mPosition = { 0, 10, -30 };

	Floor* floor = new Floor();
	AddActor(floor);
	floor->mTransform->mPosition = { 0, 15, -10 };

    Floor* leftWall = new Floor();
    AddActor(leftWall);
    leftWall->mTransform->mScale = { 5, 5, 20 };
    leftWall->mTransform->mPosition = { 10, 10, -10 };

    Floor* rightWall = new Floor();
    AddActor(rightWall);
    rightWall->mTransform->mScale = leftWall->mTransform->mScale;
    rightWall->mTransform->mPosition = { -10, 10, -10 };

    Floor* ceiling = new Floor();
    AddActor(ceiling);
    ceiling->mTransform->mPosition = { 0, 4, -10 };

    Floor* back = new Floor();
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
        float z = static_cast<float>(row) * -2.0f;  // Push row forward

        Pin* pin = new Pin();
        pin->mTransform->mPosition = { x * 1.5f, 10, z };
        AddActor(pin);
    }
}

void GLTestScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void GLTestScene::Render()
{
	Scene::Render();
}
