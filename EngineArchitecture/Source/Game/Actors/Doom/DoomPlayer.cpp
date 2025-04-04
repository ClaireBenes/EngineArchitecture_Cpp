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

	SpriteRenderComponent* slingshot = new SpriteRenderComponent(this, AssetManager::GetTexture("lance"));
	slingshot->SetNewDimensions(500, 380);
	slingshot->SetNewPositions(0, -300);

	AssetManager::LoadTexture(*mScene->GetRenderer(), "Resources/Textures/whiteOutlineCrosshair.png", "crosshair");

	SpriteRenderComponent* cursor = new SpriteRenderComponent(this, AssetManager::GetTexture("crosshair"));
	cursor->SetNewDimensions(64, 64);
}

void DoomPlayer::Update()
{
	Actor::Update();

	mCamera->mTransform->mPosition = mTransform->mPosition; 
	mCamera->mTransform->mRotation = mTransform->mRotation;
}
