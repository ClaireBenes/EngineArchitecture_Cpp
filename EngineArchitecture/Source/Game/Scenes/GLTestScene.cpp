#include "GLTestScene.h"

#include "Engine/Manager/AssetManager.h"
#include "Engine/Renderer/RendererGL.h"
#include "Engine/GameTool/Visual/Mesh/Mesh.h"

#include "Game/Actors/Wall.h"

void GLTestScene::Start()
{
	SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	mCamera = new Camera();
	AddActor(mCamera);
	mCamera->mTransform->mPosition = { 0,0,-10 };

	AssetManager::LoadTexture(*GetRenderer(), "Resources/wall.jpg", "wall");
	RendererGL::CubeMesh->AddTexture(&AssetManager::GetTexture("wall"));

	Wall* wall = new Wall();
	wall->mTransform->mPosition.x = 0;
	wall->mTransform->mScale = 0.5f;
	AddActor(wall);

	Wall* cube = new Wall();
	cube->mTransform->mPosition.x = 2;
	cube->mTransform->mPosition.y = -1;
	cube->mTransform->mPosition.z = 5;
	cube->mTransform->mScale = 1.5f;
	AddActor(cube);
}

void GLTestScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void GLTestScene::Render()
{
	Scene::Render();
}
