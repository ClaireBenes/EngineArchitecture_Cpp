#include "Wall.h"

#include "Engine/GameTool/Visual/Render/Sprite/SpriteRenderComponent.h"
#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"

#include "Engine/GameTool/Visual/Mesh/Mesh.h"
#include "Engine/Renderer/RendererGL.h"
#include "Engine/Manager/AssetManager.h"

#include "Engine/GameTool/Utility/Maths.h"

void Wall::Start()
{
	mPinMesh = new Mesh();
	mPinMesh = AssetManager::LoadMesh("pin.obj", "pin");
	mPinMesh->SetShaderProgram(RendererGL::GetMeshShaderProgram());

	Actor::Start();
}

void Wall::SetupComponents()
{
	//SpriteRenderComponent* spriteComponent = new SpriteRenderComponent(this, AssetManager::GetTexture("wall"));

	AssetManager::LoadTexture(*mScene->GetRenderer(), "Resources/Textures/pin.png", "pin");

	mTransform->mScale = 0.5f;
	mTransform->RotatePitch(180);

	mPinMesh->AddTexture(&AssetManager::GetTexture("pin"));

	MeshComponent* meshComponent = new MeshComponent(this, mPinMesh);
}

void Wall::Update()
{
	static float gameTime = 0.0f;
	gameTime += Time::deltaTime;
	//mTransform->mScale = 0.5f + Maths::Abs(Maths::Sin(gameTime * 0.75f) * 2.0f);

	/*mTransform->RotateRoll(Time::deltaTime * 90.0f);
	mTransform->RotatePitch(Time::deltaTime * 45.0f);
	mTransform->RotateRoll(Time::deltaTime * 10.0f);*/
}

void Wall::Destroy()
{
	delete mPinMesh;
}
