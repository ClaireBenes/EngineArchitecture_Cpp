#include "SpaceInvaders.h"

#include "Engine/Window.h"
#include "Game/Actors/Player.h"
#include "Game/Actors/Bush.h"

void SpaceInvaders::Start()
{
	Vector2 winDimension = mWindow->GetDimensions();

	player = new Player();
	player->mTransform.mPosition = winDimension / 2;
	AddActor(player);

	Bush* bush = new Bush();
	bush->mTransform.mPosition = winDimension / 2;
	bush->mTransform.mPosition.y = bush->mTransform.mPosition.y - 100;
	bush->mTransform.mPosition.x = bush->mTransform.mPosition.x + 200;
	AddActor(bush);
}

void SpaceInvaders::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void SpaceInvaders::Render()
{
	Scene::Render();
}
