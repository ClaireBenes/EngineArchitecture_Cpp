#pragma once

class Actor;

class Component
{
public:
	Component(float pUpdateOrder = 100);
	virtual~Component();

	virtual void OnStart();
	virtual void Update();
	virtual void OnEnd();

	void SetActive(bool isActive);
	void SetOwner(Actor* pOwner);

	int GetUpdateOrder() const;

protected:
	Actor* mOwner = nullptr;

private:
	bool mIsActive = true;
	int mUpdateOrder;
};

