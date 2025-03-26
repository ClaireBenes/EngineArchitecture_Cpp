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
	AssetManager::LoadTexture(*mScene->GetRenderer(), "Resources/Textures/wall.jpg", "wall");

	mTransform->mScale = { 10.0f, 1.0f, 10.0f };
	//mTransform->RotatePitch(180);

	mFloorMesh->AddTexture(AssetManager::GetTexture("wall"));

	MeshComponent* meshComponent = new MeshComponent(this, mFloorMesh);
	BoxColliderComponent* boxComponent = new BoxColliderComponent(this);
}
