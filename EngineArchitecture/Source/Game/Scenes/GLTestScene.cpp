#include "GLTestScene.h"

#include "Game/Actors/Wall.h"

void GLTestScene::Start()
{
	Wall* wall = new Wall();
	AddActor(wall);
}

void GLTestScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void GLTestScene::Render()
{
	Scene::Render();
}
