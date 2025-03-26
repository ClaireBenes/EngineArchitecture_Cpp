#pragma once

class IRenderer;

class DebugRenderInterface
{
public:
	// TODO : Have it work with the draw Refactor
	virtual void DebugRender(IRenderer* renderer) = 0;
};