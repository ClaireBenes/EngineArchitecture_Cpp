#pragma once

#include "Engine/GameTool/Component.h"
#include "Engine/GameTool/Vector/Vector2.h"

class ColliderComponent;

class MoveComponent : public Component
{
public:
	MoveComponent(Actor* pOwner, int pUpdateOrder = 100);
	MoveComponent() = delete;
	MoveComponent(const MoveComponent&) = delete;
	MoveComponent& operator= (const MoveComponent&) = delete;

	Vector2 GetSpeed() const;
	void SetSpeed(Vector2 pSpeed);

	void Update() override;

	void SetCollider(ColliderComponent* pCollider);
	bool CheckCollision();

protected:
	Vector2 mSpeed;

private:
	ColliderComponent* mCollidercomponent = nullptr;
};

