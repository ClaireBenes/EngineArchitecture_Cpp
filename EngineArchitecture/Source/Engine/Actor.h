#pragma once

#include "Engine/Scene.h"
#include "Engine/Transform2D.h"
#include "Engine/Component.h"

#include <vector>


enum class ActorState
{
	Active,
	Paused,
	Dead
};


class Actor
{
public:
	Actor();

	void SetScene(Scene* pScene);
	void AddComponent(Component* pComponent);
	void RemoveComponent(Component* pComponent);

	void SetActive(bool isActive);

	virtual void SetupComponents() = 0;
	virtual void Start();
	virtual void Update();
	virtual void Destroy();

	Transform2D mTransform{};

private:
	Scene* mScene = nullptr;
	ActorState mState = ActorState::Active;
	std::vector<Component*> mComponentList{};
	

};




