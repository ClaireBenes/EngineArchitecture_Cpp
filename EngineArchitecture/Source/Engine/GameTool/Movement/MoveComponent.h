#pragma once

#include "Engine/GameTool/Component.h"
#include "Engine/GameTool/Utility/Vector/Vector3.h"

class ColliderComponent;

class MoveComponent : public Component
{
public:
	MoveComponent(Actor* pOwner, int pUpdateOrder = 100);
	MoveComponent() = delete;
	MoveComponent(const MoveComponent&) = delete;
	MoveComponent& operator= (const MoveComponent&) = delete;

	Vector3 GetSpeed() const;
	void SetSpeed(Vector3 pSpeed);
	void AddForce(Vector3 pForce);

	void Update() override;

	void SetCollider(ColliderComponent* pCollider);
	bool CheckCollision();

	// - == up && + == down
	Vector3 mGravityDirection = { 0, 15, 0 };
	Vector3 mVelocity = Vector3::Zero;

	bool mInCollision = false;

protected:
	Vector3 mSpeed;

private:
	ColliderComponent* mCollidercomponent = nullptr;
};

