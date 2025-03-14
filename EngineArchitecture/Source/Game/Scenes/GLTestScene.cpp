#include "GLTestScene.h"

#include "Game/Actors/Wall.h"

#include "Game/Actors/Bush.h"

void GLTestScene::Start()
{
	SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	mCamera = new Camera();
	AddActor(mCamera);
	mCamera->mTransform->mPosition = { 0,0,-10 };

	//Bush* platform = new Bush();
	//AddActor(platform);

	Wall* wall = new Wall();
	AddActor(wall);

	//Wall* cube = new Wall();
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
