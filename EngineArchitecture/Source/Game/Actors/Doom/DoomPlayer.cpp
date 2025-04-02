#include "DoomPlayer.h"

#include "Game/Controller/FPSController.h"

void DoomPlayer::Start()
{
	mCamera = new Camera();
	mScene->AddActor(mCamera);

	mMoveComponent = new FPSController(this);

	Actor::Start();
}

void DoomPlayer::SetupComponents()
{
}

void DoomPlayer::Update()
{
	Actor::Update();

	mCamera->mTransform->mPosition = mTransform->mPosition; 
	mCamera->mTransform->mRotation = mTransform->mRotation;
}
