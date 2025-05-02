#include "DoomPlayer.h"

#include "Game/Controller/FPSController.h"
#include "Engine/Renderer/RendererGL.h"

#include "Engine/Manager/AssetManager.h"
#include "Engine/GameTool/Visual/Render/Sprite/SpriteRenderComponent.h"
#include "Engine/GameTool/Collision/BoxColliderComponent.h"

void DoomPlayer::Start()
{
	mCamera = new Camera();
	mScene->AddActor(mCamera);

	mTransform->mScale = { 1.0f, 1.5f, 1.8f };

	Actor::Start();
}

void DoomPlayer::SetupComponents()
{
	Actor::SetupComponents();

	mBoxComponent = new BoxColliderComponent(this, { { -1, -1.8, -0.5 }, { 1, 1.8, 0.5 } });

	mMoveComponent = new FPSController(this);
	mMoveComponent->SetCollider(mBoxComponent);
	mMoveComponent->mGravityDirection = -Vector3::Up * 10;
	mMoveComponent->mFriction = 10.0f;
	mMoveComponent->mVelocity = Vector3::Zero;

	// ---- UI ----
	// Lance Pierre
	AssetManager::LoadTexture(*mScene->GetRenderer(), "Resources/Textures/lancePierre.png", "lance");

	SpriteRenderComponent* slingshot = new SpriteRenderComponent(this, AssetManager::GetTexture("lance"));
	slingshot->SetNewDimensions(500, 380);
	slingshot->SetNewPositions(0, -300);

	//Cursor
	AssetManager::LoadTexture(*mScene->GetRenderer(), "Resources/Textures/whiteOutlineCrosshair.png", "crosshair");

	SpriteRenderComponent* cursor = new SpriteRenderComponent(this, AssetManager::GetTexture("crosshair"));
	cursor->SetNewDimensions(64, 64);

	//Heart
	AssetManager::LoadTexture(*mScene->GetRenderer(), "Resources/Textures/Heart.png", "heart");

	float yPos = -570;
	for (int i = 0; i < mHealth; i++)
	{
		Actor* heart = new Actor();
		SpriteRenderComponent* heartImage = new SpriteRenderComponent(heart, AssetManager::GetTexture("heart"));
		heartImage->SetNewDimensions(128, 128);
		heartImage->SetNewPositions(yPos, 300);

		mScene->AddActor(heart);
		mAllHearts.push_back(heart);

		yPos += 100;
	} 
}

void DoomPlayer::Update()
{
	Actor::Update();

	mCamera->mTransform->mPosition = mTransform->mPosition; 
	mCamera->mTransform->mRotation = mTransform->mRotation;
}

void DoomPlayer::TakeDamage(int damage)
{
	mHealth -= damage;

	if (!mAllHearts.empty())
	{
		for (int i = 0; i < damage; i++)
		{
			mAllHearts.back()->Destroy();
			mAllHearts.pop_back();
		}
	}

	if (mHealth <= 0)
	{
		//Destroy();
	}
}
