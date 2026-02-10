#include "TheDescentPlayer.h"

#include "Engine/Renderer/RendererGL.h"

#include "Engine/Manager/AssetManager.h"
#include "Engine/GameTool/Visual/Render/Sprite/SpriteRenderComponent.h"
#include "Engine/GameTool/Visual/Render/ScreenEffectRenderComponent.h"
#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"
#include "Engine/GameTool/Collision/BoxColliderComponent.h"

#include "Engine/Engine.h"

#include "Game/Controller/PilotController.h"

void TheDescentPlayer::Start()
{
	mCamera = new Camera();
	mScene->AddActor(mCamera);

	mTransform->mScale = { 1.0f, 1.5f, 1.8f };

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
	Shader godRayVertexShader = Shader();
	Shader godRayFragShader = Shader();

	godRayVertexShader.Load("FullScreen.vert", ShaderType::VERTEX);
	godRayFragShader.Load("ArtShader.frag", ShaderType::FRAGMENT);

	mGodRayScreenEffect = new ScreenEffectRenderComponent(this);
	mGodRayScreenEffect->GetShaderProgram().Compose({ &godRayVertexShader, &godRayFragShader });

	mGodRayScreenEffect->GetShaderProgram().setVector3f("uDimensions", Vector3(mScene->GetWindow()->GetDimensions().x, mScene->GetWindow()->GetDimensions().y, 1.0));

	// Water Distortion Shader
	Shader distortionVertexShader = Shader();
	Shader distortionFragShader = Shader();

	distortionVertexShader.Load("FullScreen.vert", ShaderType::VERTEX);
	distortionFragShader.Load("WaterDistortion.frag", ShaderType::FRAGMENT);

	mDistortionScreenEffect = new ScreenEffectRenderComponent(this);
	mDistortionScreenEffect->GetShaderProgram().Compose({ &distortionVertexShader, &distortionFragShader });

	mDistortionScreenEffect->GetShaderProgram().setVector3f("uDimensions", Vector3(mScene->GetWindow()->GetDimensions().x, mScene->GetWindow()->GetDimensions().y, 1.0));
	mDistortionScreenEffect->GetShaderProgram().setFloat("uSpeed", 0.3f);

	// ---- UI ----
	// CockPit
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
}

void TheDescentPlayer::Update()
{
	Actor::Update();

	mCamera->mTransform->mPosition = mTransform->mPosition; 
	mCamera->mTransform->mRotation = mTransform->mRotation;

	// Update post process
	mGodRayScreenEffect->GetShaderProgram().Use();
	mGodRayScreenEffect->GetShaderProgram().setFloat("uTime", Time::GetGameTime());

	mDistortionScreenEffect->GetShaderProgram().Use();
	mDistortionScreenEffect->GetShaderProgram().setFloat("uTime", Time::GetGameTime());
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
