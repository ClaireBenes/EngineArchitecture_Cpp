#include "DoomPlayer.h"

#include "Game/Controller/FPSController.h"
#include "Engine/Renderer/RendererGL.h"

#include "Engine/Manager/AssetManager.h"
#include "Engine/GameTool/Visual/Render/Sprite/SpriteRenderComponent.h"
#include "Engine/GameTool/Collision/BoxColliderComponent.h"

#include "Engine/Engine.h"

void DoomPlayer::Start()
{
	mCamera = new Camera();
	mScene->AddActor(mCamera);

	mTransform->mScale = { 1.0f, 1.5f, 1.8f };

	Engine::mIsGamePaused = false;

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
	SpriteRenderComponent* slingshot = new SpriteRenderComponent(this, AssetManager::GetTexture("lance"));
	slingshot->SetNewDimensions(500, 380);
	slingshot->SetNewPositions(0, -300);

	//Cursor
	SpriteRenderComponent* cursor = new SpriteRenderComponent(this, AssetManager::GetTexture("crosshair"));
	cursor->SetNewDimensions(64, 64);

	//Lose Screen
	loseScreen = new SpriteRenderComponent(this, AssetManager::GetTexture("loseScreen"), 120);
	loseScreen->SetNewDimensions(0,0);

	//Win Screen
	winScreen = new SpriteRenderComponent(this, AssetManager::GetTexture("winScreenTex"), 120);
	winScreen->SetNewDimensions(0, 0);


	//Heart
	float heartXPos = -570;
	for (int i = 0; i < mHealth; i++)
	{
		AddHUDHeart(heartXPos);

		heartXPos += mHeartXOffset;
	} 

	// Ammo
	for(int row = 0; row < (mAmmo / 10); ++row)
	{
		for(int col = 0; col < mAmmoPerLines; ++col)
		{
			float x = mAmmoXPos + col * mAmmoXOffset;
			float y = mAmmoYPos + row * mAmmoYOffset;

			AddHUDRock(x, y);
		}
	}
}

void DoomPlayer::Update()
{
	Actor::Update();

	mCamera->mTransform->mPosition = mTransform->mPosition; 
	mCamera->mTransform->mRotation = mTransform->mRotation;
}

void DoomPlayer::EndGame(bool isWin)
{
	if (isWin) 
	{
		winScreen->SetNewDimensions(mScene->GetWindow()->GetDimensions().x + 40, mScene->GetWindow()->GetDimensions().y + 40);
	}
	else 
	{
		loseScreen->SetNewDimensions(mScene->GetWindow()->GetDimensions().x + 40, mScene->GetWindow()->GetDimensions().y + 40);
	}

	Engine::mIsGamePaused = true;
	mIsGameEnd = true;
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
		EndGame(false);
	}
}

void DoomPlayer::RestoreHealth()
{
	if (mHealth < mMaxHealth)
	{
		mHealth += 1;

		AddHUDHeart(mAllHearts.back()->GetComponentOfType<SpriteRenderComponent>()->mRectangle.position.x + mHeartXOffset);
	}
}

void DoomPlayer::AddHUDHeart(float xPos, float yPos)
{
	Actor* heart = new Actor();
	SpriteRenderComponent* heartImage = new SpriteRenderComponent(heart, AssetManager::GetTexture("heartHUD"));
	heartImage->SetNewDimensions(121, 115);

	heartImage->SetNewPositions(xPos, yPos);

	mScene->AddActor(heart);
	mAllHearts.push_back(heart);
}

void DoomPlayer::AddHUDRock(float xPos, float yPos)
{
	Actor* rock = new Actor();
	SpriteRenderComponent* rockImage = new SpriteRenderComponent(rock, AssetManager::GetTexture("rockHUD"));
	rockImage->SetNewDimensions(50, 50);
	rockImage->SetNewPositions(xPos, yPos);

	mScene->AddActor(rock);
	mAllAmmos.push_back(rock);
}

int DoomPlayer::GetAmmo()
{
	return mAmmo;
}

void DoomPlayer::RestoreAmmo()
{
	for(int i = 0; i < mAmmoToPickUp; ++i)
	{
		int col = (mAmmo + i) % mAmmoPerLines;
		int row = (mAmmo + i) / mAmmoPerLines;

		float x = mAmmoXPos + col * mAmmoXOffset;
		float y = mAmmoYPos + row * mAmmoYOffset;

		AddHUDRock(x, y);
	}

	mAmmo += mAmmoToPickUp;
}

void DoomPlayer::Shoot()
{
	mAmmo -= 1;

	if(!mAllAmmos.empty())
	{
		mAllAmmos.back()->Destroy();
		mAllAmmos.pop_back();
	}
}
