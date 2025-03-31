#include "DoomPlayer.h"

void DoomPlayer::Start()
{
	mCamera = new Camera();
	mScene->AddActor(mCamera);

	Actor::Start();
}

void DoomPlayer::SetupComponents()
{
}

void DoomPlayer::Update()
{
	Actor::Update();
}
