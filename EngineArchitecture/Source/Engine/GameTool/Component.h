#pragma once

class Actor;
class IRenderer;

class Component
{
public:
	//Functions
	Component(int pUpdateOrder = 100);

	virtual void OnStart() {};
	virtual void Update() {};
	virtual void OnEnd() {};

	void SetActive(bool isActive);
	void SetOwner(Actor* pOwner);

	int GetUpdateOrder() const;

//Variables
protected:
	Actor* mOwner = nullptr;

private:
	bool mIsActive = true;
	int mUpdateOrder;
};

