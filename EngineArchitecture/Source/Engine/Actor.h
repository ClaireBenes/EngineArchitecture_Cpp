#pragma once

#include "Engine/Scene.h"
#include "Engine/Transform2D.h"
#include "Engine/Component.h"

#include <vector>;


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

	void Start();

	void AttachScene(Scene* rScene);
	void AddComponent(Component* rComponent);
	void RemoveComponent(Component* rComponent);

	void SetActive();
	void Update();
	void Destroy();

private:
	Scene* mScene = nullptr;
	Transform2D* mTransform = nullptr;
	ActorState mState = ActorState::Active;
	std::vector<Component*> mComponentList{};
	

};




