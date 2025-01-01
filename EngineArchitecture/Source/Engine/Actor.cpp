#include "Actor.h"

#include "RenderComponent.h"

void Actor::Start()
{
	SetupComponents();

	for(Component* myComponent : mComponentList)
	{
		myComponent->OnStart();
	}
}

void Actor::SetScene(Scene* pScene)
{
	mScene = pScene;
}

void Actor::AddComponent(Component* pComponent)
{
	mComponentList.push_back(pComponent);

	if(RenderComponent* pRenderComponent = dynamic_cast<RenderComponent*>(pComponent))
	{
		mRenderComponents.push_back(pRenderComponent);
	}
}

void Actor::RemoveComponent(Component* pComponent)
{
	auto it = std::find(mComponentList.begin(), mComponentList.end(), pComponent);
	if(it == mComponentList.end())
	{
		return;
	}

	if(RenderComponent* pRenderComponent = dynamic_cast<RenderComponent*>(pComponent))
	{
		auto itRender = std::find(mRenderComponents.begin(), mRenderComponents.end(), pRenderComponent);

		if(itRender != mRenderComponents.end())
		{
			mRenderComponents.erase(itRender);
		}
	}

	delete pComponent;
	mComponentList.erase(it);
}

void Actor::SetActive(bool isActive)
{
	if(isActive)
	{
		mState = ActorState::Active;
	}
	else
	{
		mState = ActorState::Paused;
	}

	for(Component* myComponent : mComponentList)
	{
		myComponent->SetActive(isActive);
	}
}

void Actor::Render(Renderer* pRenderer)
{
	for(RenderComponent* renderComponent : mRenderComponents)
	{
		renderComponent->Render(pRenderer);
	}
}

void Actor::Update()
{
	for(Component* myComponent : mComponentList)
	{
		myComponent->Update();
	}
}

void Actor::Destroy()
{
	for(Component* myComponent : mComponentList)
	{
		myComponent->OnEnd();
	}
}
