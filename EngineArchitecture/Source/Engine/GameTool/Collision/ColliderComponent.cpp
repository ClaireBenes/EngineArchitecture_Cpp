#include "ColliderComponent.h"

#include "Engine/GameTool/Actor.h"
#include "Engine/Renderer/IRenderer.h"
#include "Engine/Manager/PhysicManager.h"

ColliderComponent::ColliderComponent(Actor* pOwner):
Component(pOwner)
{
}

void ColliderComponent::OnStart()
{
	mOwner->mScene->GetRenderer()->AddDebugRender(this);
	PhysicManager::Instance().AddComponent(this);
}

void ColliderComponent::OnEnd()
{
	mOwner->mScene->GetRenderer()->RemoveDebugRender(this);
	PhysicManager::Instance().RemoveComponent(this);
}
