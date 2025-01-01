#include "SpaceInvaders.h"

#include "Engine/Window.h"
#include "Player.h"

void SpaceInvaders::Start()
{
	Vector2 winDimension = mWindow->GetDimensions();

	Player* player = new Player();
	player->mTransform.mPosition = winDimension / 2;
	AddActor(player);
}

void SpaceInvaders::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void SpaceInvaders::Render()
{
	Scene::Render();
}

void SpaceInvaders::OnInput(SDL_Event event)
{
}
