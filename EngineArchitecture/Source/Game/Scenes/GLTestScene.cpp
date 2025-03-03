#include "GLTestScene.h"

#include "Game/Actors/Bush.h"

void GLTestScene::Start()
{
	Bush* platform = new Bush();
	AddActor(platform);
}

void GLTestScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void GLTestScene::Render()
{
	Scene::Render();
}
