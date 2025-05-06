#pragma once

#include "Engine/GameTool/Actor.h"

class BoxColliderComponent;

class Door : public Actor
{
public:
	void Start() override;
	void SetupComponents() override;
	void Update() override;

	void OnCollide(Actor* collidedActor) override;
	void SetPlayer(Actor* player);

	float GetYawFromQuaternion(const Quaternion& q);

private:
	Actor* mPlayer = nullptr;
	BoxColliderComponent* mBoxComponent = nullptr;

	bool mIsturning = false;
	float mCurrentYaw = 0.0f; // degrees
};

