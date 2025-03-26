#pragma once

#include "ColliderComponent.h"
#include "Engine/GameTool/Utility/Geometry/Box.h"

//Rectangle
class BoxColliderComponent : public ColliderComponent
{
public:
	BoxColliderComponent(Actor* pOwner, Box pBox = {});

	void DebugRender(IRenderer* pRenderer) override;

	//AABB Collision Check
	bool Collision(const ColliderComponent* pComponent) override;

	Box GetWorldBox() const;

	Box mBox;
};

