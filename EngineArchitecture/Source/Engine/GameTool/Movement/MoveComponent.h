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

	Vector2 GetRotationSpeed() const;
	void SetRotationSpeed(Vector2 pRotationSpeed);

	virtual void Update() override;
	virtual Vector3 GetDesiredPos();

	void SetCollider(ColliderComponent* pCollider);
	ColliderComponent* CheckCollision();

	// - == up && + == down
	Vector3 mGravityDirection = Vector3::Zero; //Vector3::Up * -15.0f;
	Vector3 mVelocity = Vector3::Zero;

	float mFriction = 0.8f;

protected:
	Vector3 mSpeed = 0;
	Vector2 mRotationSpeed = 0;

private:
	ColliderComponent* mCollidercomponent = nullptr;
};

