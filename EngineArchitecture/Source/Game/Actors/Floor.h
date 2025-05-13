#pragma once

#include "Engine/GameTool/Actor.h"

class Mesh;

class Floor : public Actor
{
public:
	void Start() override;
	void SetupComponents() override;

	void SetTextureIndex(size_t newIndex);
	void SetTextureTiling(float x, float y);

private:
	size_t mTextureIndex = 0;
	Vector2 mTextureTiling = (55, 55);
};

