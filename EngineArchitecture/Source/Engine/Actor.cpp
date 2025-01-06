#include "Actor.h"

#include "RenderComponent.h"

void Actor::Start()
{
	//Setting up all actors component
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

	//check if the component is a render component
	if(RenderComponent* pRenderComponent = dynamic_cast<RenderComponent*>(pComponent))
	{
		mRenderComponents.push_back(pRenderComponent);
	}

	//***************** not sure ? ************************//
	pComponent->OnStart();
}

//Remove a specific component
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

//Set state of actor (active or paused)
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
