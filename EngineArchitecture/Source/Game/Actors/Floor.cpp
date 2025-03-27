#include "Floor.h"
#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"
#include "Engine/GameTool/Visual/Mesh/Mesh.h"

#include "Engine/GameTool/Collision/BoxColliderComponent.h"
#include "Engine/Renderer/RendererGL.h"
#include "Engine/Manager/AssetManager.h"

void Floor::Start()
{
	mFloorMesh = AssetManager::LoadMesh("cube.obj", "cube");
	mFloorMesh->SetShaderProgram(RendererGL::GetMeshShaderProgram());

	Actor::Start();
}

void Floor::SetupComponents()
{
	AssetManager::LoadTexture(*mScene->GetRenderer(), "Resources/Textures/bowling.png", "floor");

	mTransform->mScale = { 5.0f, 1.0f, 20.0f };
	//mTransform->RotateYaw(90);

	mFloorMesh->AddTexture(AssetManager::GetTexture("floor"));

	MeshComponent* meshComponent = new MeshComponent(this, mFloorMesh);
	BoxColliderComponent* boxComponent = new BoxColliderComponent(this);
}
