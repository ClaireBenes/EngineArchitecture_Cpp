#pragma once

class Actor;

class Component
{
public:
	Component(Actor* pOwner, float pUpdateOrder = 100);
	Component() = delete;
	virtual~Component();

	virtual void OnStart();
	virtual void Update();
	virtual void OnEnd();

private:
	bool mIsActive = true;
	int mUpdateOrder;
	Actor& mOwner;
};

