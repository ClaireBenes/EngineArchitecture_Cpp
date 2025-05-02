#pragma once

class Actor;
class IRenderer;

/*
Base class for all components that can be attached to an Actor.
Components define behavior or functionality and are updated each frame.
They can respond to events such as start, update, end, or world transform changes.
 */
class Component
{
public:
	//Functions

	/*
	 * Constructor for Component.
	 * @param pOwner The actor that owns this component.
	 * @param pUpdateOrder The update order priority for the component (default: 100).
	 */
	Component(Actor* pOwner, int pUpdateOrder = 100);
	virtual ~Component() {};

	/*
	Called when the component is initialized (during actor start).
	This can be used to perform any setup operations for the component.
	 */
	virtual void OnStart() {};
	/*
	Called every frame to update the component.
	This can be used to perform actions that need to be updated periodically.
	 */
	virtual void Update() {};
	/*
	Called when the component is about to be destroyed (during actor destruction).
	This can be used to clean up or release any resources.
	 */
	virtual void OnEnd() {};
	/*
	Called when the world transform of the actor is updated.
	This allows the component to react to changes in the actor's world transform.
	 */
	virtual void OnUpdateWorldTrandform() {};

	/*
	 * Sets the active status of the component.
	 * @param isActive Whether the component should be active or not.
	 */
	void SetActive(bool isActive);
	/*
	 * Sets the actor that owns this component.
	 * @param pOwner The actor to assign as the owner of this component.
	 */
	void SetOwner(Actor* pOwner);

	/*
	 * Returns the update order of the component.
	 * Components with lower update orders are updated first.
	 * @return The update order of the component.
	 */
	int GetUpdateOrder() const;
	/*
	 * Returns the actor that owns this component.
	 * @return The actor that owns this component.
	 */
	Actor* GetOwner() const;

//Variables
protected:
	Actor* mOwner = nullptr; // The actor that owns this component.

private: 
	bool mIsActive = true; // The active status of the component (default: active).
	int mUpdateOrder; // The order in which this component should be updated.
};

