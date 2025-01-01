#include "Scene.h"

Scene::Scene()
{
}

void Scene::SetWindow(Window* pWindow)
{
	mWindow = pWindow;
}

void Scene::SetRenderer(Renderer* pRenderer)
{
	mRenderer = pRenderer;
}
