#include "Wall.h"

#include "Engine/GameTool/Visual/Render/Sprite/SpriteRenderComponent.h"
#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"
#include "Engine/Renderer/RendererGL.h"
#include "Engine/Manager/AssetManager.h"
#include "Engine/GameTool/Utility/Maths.h"

void Wall::SetupComponents()
{
	//SpriteRenderComponent* spriteComponent = new SpriteRenderComponent(this, AssetManager::GetTexture("wall"));

	mTransform->mScale = 0.5f;
	mTransform->RotateRoll(45);
	mTransform->RotatePitch(45);
	mTransform->RotateRoll(45);

	MeshComponent* meshComponent = new MeshComponent(this, RendererGL::CubeMesh);
}

void Wall::Update()
{
	static float gameTime = 0.0f;
	gameTime += Time::deltaTime;
	mTransform->mScale = 0.5f + Maths::Abs(Maths::Sin(gameTime * 0.75f) * 2.0f);

	mTransform->RotateRoll(Time::deltaTime * 90.0f);
	mTransform->RotatePitch(Time::deltaTime * 45.0f);
	mTransform->RotateRoll(Time::deltaTime * 10.0f);
}

void Wall::Destroy()
{
}
