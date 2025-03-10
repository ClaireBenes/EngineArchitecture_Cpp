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

	float GetRotationSpeed() const;
	void SetRotationSpeed(float pRotationSpeed);

	void Update() override;

	void SetCollider(ColliderComponent* pCollider);
	bool CheckCollision();

	// - == up && + == down
	Vector3 mGravityDirection = Vector3::Zero; //Vector3::Up * -15.0f;
	Vector3 mVelocity = Vector3::Zero;

	bool mInCollision = false;

protected:
	Vector3 mSpeed = 0;
	float mRotationSpeed = 0;

private:
	ColliderComponent* mCollidercomponent = nullptr;
};

