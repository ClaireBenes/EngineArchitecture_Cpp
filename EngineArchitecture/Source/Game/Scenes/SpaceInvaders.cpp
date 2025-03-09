#include "SpaceInvaders.h"

#include "Engine/Window.h"
#include "Game/Actors/Player.h"
#include "Game/Actors/Bush.h"

void SpaceInvaders::Start()
{
	Vector2 winDimension = mWindow->GetDimensions();

	player = new Player();
	player->mTransform->mPosition = winDimension / 2;
	AddActor(player);

	Bush* platform = new Bush();
	platform->mTransform->mPosition = player->mTransform->mPosition;
	platform->mTransform->mPosition.y += 200;

	Bush* secondPlatform = new Bush();
	secondPlatform->mTransform->mPosition = Vector2(150, 530);

	AddActor(platform);
	AddActor(secondPlatform);
}

void SpaceInvaders::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void SpaceInvaders::Render()
{
	Scene::Render();
}
