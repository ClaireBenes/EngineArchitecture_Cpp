#pragma once

class IRenderer;

class DebugRenderInterface
{
public:
	virtual void DebugRender(IRenderer* renderer) = 0;
};