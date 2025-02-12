#pragma once

#include "Scene.h"
#include "Transform/Transform2D.h"
#include "Component.h"
#include "Engine/Time.h"

#include <vector>

class RenderComponent;
class ColliderComponent;
class AssetManager;

//All actor possible state
enum class ActorState
{
	Active,
	Paused,
	Dead
};


class Actor
{
public:
	virtual ~Actor();

	//Functions
	void SetScene(Scene* pScene);
	void AddComponent(Component* pComponent);
	void RemoveComponent(Component* pComponent);

	void SetActive(bool isActive);
	void Render(Renderer* pRenderer);

	ActorState GetState() const;

	virtual void SetupComponents() = 0;
	virtual void Start();
	virtual void Update();
	virtual void Destroy();

	//Variables
	Transform2D mTransform{};

protected:
	Scene* mScene = nullptr;

private:
	ActorState mState = ActorState::Paused;

	std::vector<Component*> mComponents{};
	std::vector<RenderComponent*> mRenderComponents{};
	std::vector<ColliderComponent*> mColliderComponents{};
};




