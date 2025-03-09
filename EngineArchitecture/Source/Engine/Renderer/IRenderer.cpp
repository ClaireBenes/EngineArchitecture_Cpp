#include "IRenderer.h"

#include "Engine/GameTool/Visual/Render/RenderComponent.h"

void IRenderer::AddRenderComponent(RenderComponent* pRenderComponent)
{
	if (pRenderComponent->GetRenderType() == RenderType::Viewport)
	{
		int spriteDrawOrder = pRenderComponent->GetDrawOrder();
		std::vector<RenderComponent*>::iterator spriteIterator;

		for (spriteIterator = mViewportRenderComponents.begin(); spriteIterator != mViewportRenderComponents.end(); ++spriteIterator)
		{
			if (spriteDrawOrder < (*spriteIterator)->GetDrawOrder()) break;
		}
		mViewportRenderComponents.insert(spriteIterator, pRenderComponent);
	}
	else if (pRenderComponent->GetRenderType() == RenderType::World)
	{
		mWorldRenderComponents.push_back(pRenderComponent);
	}
}

void IRenderer::RemoveRenderComponent(RenderComponent* pRenderComponent)
{
	if (pRenderComponent->GetRenderType() == RenderType::Viewport)
	{
		auto it = std::find(mViewportRenderComponents.begin(), mViewportRenderComponents.end(), pRenderComponent);
		if (it != mViewportRenderComponents.end())
		{
			mViewportRenderComponents.erase(it);
		}
	}
	else if (pRenderComponent->GetRenderType() == RenderType::World)
	{
		auto it = std::find(mWorldRenderComponents.begin(), mWorldRenderComponents.end(), pRenderComponent);
		if (it != mWorldRenderComponents.end())
		{
			mWorldRenderComponents.erase(it);
		}
	}

}
