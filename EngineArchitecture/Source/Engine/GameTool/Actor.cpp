#include "Actor.h"

#include "Visual/Render/RenderComponent.h"
#include "Collision/ColliderComponent.h"
#include "Engine/Manager/AssetManager.h"
#include "Visual/Render/Sprite/SpriteRenderComponent.h"

#include "Engine/Engine.h"

void Actor::Start()
{
	//Setting up all actors component
	SetupComponents();

	for(Component* myComponent : mComponents)
	{
		myComponent->OnStart();
	}

	mState = ActorState::Active;
}

Actor::Actor()
{
	mTransform = new Transform(this);
}

Actor::~Actor()
{
	for (Component* pComponent : mComponents)
	{
		pComponent->OnEnd();
		delete pComponent;
	}
}

void Actor::SetScene(Scene* pScene)
{
	mScene = pScene;
}

void Actor::AddComponent(Component* pComponent)
{
	mComponents.push_back(pComponent);

	//check if the component is a render component
	if(RenderComponent* pRenderComponent = dynamic_cast<RenderComponent*>(pComponent))
	{
		mRenderComponents.push_back(pRenderComponent);
	}

	//check if the component is a collider component
	if(ColliderComponent* pColliderComponent = dynamic_cast<ColliderComponent*>( pComponent ))
	{
		mColliderComponents.push_back(pColliderComponent);
	}
}

//Remove a specific component
void Actor::RemoveComponent(Component* pComponent)
{
	auto it = std::find(mComponents.begin(), mComponents.end(), pComponent);
	if(it == mComponents.end())
	{
		return;
	}

	//check if the component is a render component
	if(RenderComponent* pRenderComponent = dynamic_cast<RenderComponent*>(pComponent))
	{
		auto itRender = std::find(mRenderComponents.begin(), mRenderComponents.end(), pRenderComponent);

		if(itRender != mRenderComponents.end())
		{
			mRenderComponents.erase(itRender);
		}
	}

	//check if the component is a collider component
	if(ColliderComponent* pColliderComponent = dynamic_cast< ColliderComponent* >( pComponent ))
	{
		auto itCollider = std::find(mColliderComponents.begin(), mColliderComponents.end(), pColliderComponent);

		if(itCollider != mColliderComponents.end())
		{
			mColliderComponents.erase(itCollider);
		}
	}

	delete pComponent;
	mComponents.erase(it);
}

void Actor::UpdateComponentsTransform()
{
	for (Component* myComponent : mComponents)
	{
		myComponent->OnUpdateWorldTrandform();
	}
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

	for(Component* myComponent : mComponents)
	{
		myComponent->SetActive(isActive);
	}
}

ActorState Actor::GetState() const
{
	return mState;
}

Vector3 Actor::GetPosition() const
{
	return mTransform->mPosition;
}

void Actor::Update()
{
	for(Component* myComponent : mComponents)
	{
		myComponent->Update();
	}
}

void Actor::Destroy()
{

}
