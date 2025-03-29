#pragma once

class Actor;
class IRenderer;

class Component
{
public:
	//Functions
	Component(Actor* pOwner, int pUpdateOrder = 100);
	virtual ~Component() {};

	virtual void OnStart() {};
	virtual void Update() {};
	virtual void OnEnd() {};
	virtual void OnUpdateWorldTrandform() {};

	void SetActive(bool isActive);
	void SetOwner(Actor* pOwner);

	int GetUpdateOrder() const;
	Actor* GetOwner() const;

//Variables
protected:
	Actor* mOwner = nullptr;

private:
	bool mIsActive = true;
	int mUpdateOrder;
};

