#include "GLTestScene.h"

#include "Game/Actors/Pin.h"
#include "Game/Actors/Floor.h"

#include "Game/Actors/Bush.h"

void GLTestScene::Start()
{
	SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	mCamera = new Camera();
	AddActor(mCamera);
	mCamera->mTransform->mPosition = { 0, 10, -10 };

	//Bush* platform = new Bush();
	//AddActor(platform);
	Floor* floor = new Floor();
	AddActor(floor);
	floor->mTransform->mPosition = { 0, 10, 0 };

	for (int i = 0; i < 10; i++)
	{
		Pin* pin = new Pin();
		pin->mTransform->mPosition = { static_cast<float>(i) * 1.5f, 0, 0 };
		AddActor(pin);
	}

	//Pin* cube = new Pin();
	//cube->mTransform->mPosition.x = 2;
	//cube->mTransform->mPosition.y = -1;
	//cube->mTransform->mPosition.z = 5;
	//cube->mTransform->mScale = 1.5f;
	//AddActor(cube);
}

void GLTestScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void GLTestScene::Render()
{
	Scene::Render();
}
