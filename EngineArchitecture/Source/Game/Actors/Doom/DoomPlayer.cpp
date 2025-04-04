#include "DoomPlayer.h"

#include "Game/Controller/FPSController.h"

#include "Engine/Manager/AssetManager.h"
#include "Engine/GameTool/Visual/Render/Sprite/SpriteRenderComponent.h"

void DoomPlayer::Start()
{
	mCamera = new Camera();
	mScene->AddActor(mCamera);

	Actor::Start();
}

void DoomPlayer::SetupComponents()
{
	mMoveComponent = new FPSController(this);

	AssetManager::LoadTexture(*mScene->GetRenderer(), "Resources/Textures/lancePierre.png", "lance");

	SpriteRenderComponent* spriteComponent = new SpriteRenderComponent(this, AssetManager::GetTexture("lance"));
	spriteComponent->SetNewDimensions(500, 380);
	spriteComponent->SetNewPositions(0, -300);
}

void DoomPlayer::Update()
{
	Actor::Update();

	mCamera->mTransform->mPosition = mTransform->mPosition; 
	mCamera->mTransform->mRotation = mTransform->mRotation;
}
