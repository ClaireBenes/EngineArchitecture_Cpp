#include "SpaceInvaders.h"

#include "Engine/Window.h"
#include "Player.h"
#include "Bush.h"

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

void SpaceInvaders::OnInput(SDL_Event event)
{
	switch(event.type)
	{
		case SDL_KEYDOWN:
			//Move player up and down
			if(event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_z)
			{
				player->StopMoving();
				player->mIsMovingUp = true;
			}
			if(event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
			{
				player->StopMoving();
				player->mIsMovingDown = true;
			}
			//Move player right and left
			if(event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
			{
				player->StopMoving();
				player->mIsMovingRight = true;
			}
			if(event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_q)
			{
				player->StopMoving();
				player->mIsMovingLeft = true;
			}
			break;

		case SDL_KEYUP:
			//stop moving player
			player->StopMoving();
			break;

		default:
			break;
	}
}
