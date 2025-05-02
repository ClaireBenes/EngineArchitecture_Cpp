#include "Platformer2D.h"

#include "Engine/Window.h"
#include "Game/Actors/Platformer/Player.h"
#include "Game/Actors/Platformer/Bush.h"

void Platformer2D::Start()
{
	Vector2 winDimension = mWindow->GetDimensions();

	player = new Player();
	player->mTransform->mPosition = winDimension / 2;
	AddActor(player);

	Bush* platform = new Bush();
	platform->mTransform->mPosition = player->mTransform->mPosition;
	platform->mTransform->mPosition.y += 200;

	Bush* secondPlatform = new Bush();
	secondPlatform->mTransform->mPosition = Vector2(platform->mTransform->mPosition.x - 250, 530);

	AddActor(platform);
	AddActor(secondPlatform);
}

void Platformer2D::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}
