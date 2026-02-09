#include "TheDescentPlayer.h"

#include "Engine/Renderer/RendererGL.h"

#include "Engine/Manager/AssetManager.h"
#include "Engine/GameTool/Visual/Render/Sprite/SpriteRenderComponent.h"
#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"
#include "Engine/GameTool/Collision/BoxColliderComponent.h"

#include "Engine/Engine.h"

#include "Game/Controller/PilotController.h"

void TheDescentPlayer::Start()
{
	mCamera = new Camera();
	mScene->AddActor(mCamera);

	mTransform->mScale = { 1.0f, 1.5f, 1.8f };

	// ----- GODS RAY -----
	mGodsRay = new Actor();
	float screenHeight = 2.0f * tan(28.0f * 0.5f * (3.14159f / 180.0f));
	float screenWidth = screenHeight * mScene->GetWindow()->GetDimensions().x / mScene->GetWindow()->GetDimensions().y;

	mGodsRay->mTransform->mScale = Vector3(screenWidth, 0.0f, screenHeight);
	mGodsRay->mTransform->mPosition = { -0.6f + mGodsRay->mTransform->mScale.x, 0.0, 1 }; //-2.5f
	mGodsRay->mTransform->RotatePitch(90);
	// ----- END GODS RAY -----

	Engine::mIsGamePaused = false;

	Actor::Start();
}

void TheDescentPlayer::SetupComponents()
{
	Actor::SetupComponents();

	mBoxComponent = new BoxColliderComponent(this, { { -1, -1.8, -0.5 }, { 1, 1.8, 0.5 } });

	mMoveComponent = new PilotController(this);
	mMoveComponent->SetCollider(mBoxComponent);
	mMoveComponent->mVelocity = Vector3::Zero;

	// God Ray Shader
	mGodRayMesh = AssetManager::LoadMesh("plane.obj", "rays");
	mGodRayMesh->SetShaderProgram(RendererGL::mArtShaderProgram);

	// ---- UI ----
	// Lance Pierre
	SpriteRenderComponent* cockpit = new SpriteRenderComponent(this, AssetManager::GetTexture("cockpit"));
	cockpit->SetNewDimensions(mScene->GetWindow()->GetDimensions().x, mScene->GetWindow()->GetDimensions().y );
	cockpit->SetNewPositions(0, 0);

	//Cursor
	SpriteRenderComponent* cursor = new SpriteRenderComponent(this, AssetManager::GetTexture("crosshair"));
	cursor->SetNewDimensions(64, 64);

	//Lose Screen
	loseScreen = new SpriteRenderComponent(this, AssetManager::GetTexture("loseScreen"), 120);
	loseScreen->SetNewDimensions(0,0);

	//Win Screen
	winScreen = new SpriteRenderComponent(this, AssetManager::GetTexture("winScreenTex"), 120);
	winScreen->SetNewDimensions(0, 0);


	// Gods Ray
	MeshComponent* meshComponent = new MeshComponent(mGodsRay, AssetManager::GetMesh("rays"));
	//mScene->AddActor(mGodsRay);
}

void TheDescentPlayer::Update()
{
	Actor::Update();

	mCamera->mTransform->mPosition = mTransform->mPosition; 
	mCamera->mTransform->mRotation = mTransform->mRotation;

	Vector3 camForward = mCamera->mTransform->Forward(); // camera forward vector
	mGodsRay->mTransform->mPosition = mCamera->mTransform->mPosition + camForward;

	mGodsRay->mTransform->LookAt(mCamera->mTransform->mPosition);
	mGodsRay->mTransform->RotatePitch(90);

	//mTransform->RotateRoll(1);

	printf("%.2f\n", mTransform->mRotation.GetRoll());
}

void TheDescentPlayer::EndGame(bool isWin)
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

void TheDescentPlayer::TakeDamage(int damage)
{
	mHealth -= damage;

	if (mHealth <= 0)
	{
		EndGame(false);
	}
}

void TheDescentPlayer::Shoot()
{
	//Do something
}
