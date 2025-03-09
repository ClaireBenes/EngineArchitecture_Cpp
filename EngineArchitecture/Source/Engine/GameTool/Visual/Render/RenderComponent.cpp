#include "RenderComponent.h"
#include "Engine/GameTool/Actor.h"
#include "Engine/Renderer/IRenderer.h"


RenderComponent::RenderComponent(Actor* pOwner)
	: Component(pOwner)
{
}

void RenderComponent::OnStart()
{
	mOwner->mScene->GetRenderer()->AddRenderComponent(this);
}

void RenderComponent::OnEnd()
{
	mOwner->mScene->GetRenderer()->RemoveRenderComponent(this);
}

int RenderComponent::GetDrawOrder() const
{
	return 0;
}
