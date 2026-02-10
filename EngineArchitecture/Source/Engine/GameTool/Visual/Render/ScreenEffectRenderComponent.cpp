#include "ScreenEffectRenderComponent.h"

ScreenEffectRenderComponent::ScreenEffectRenderComponent(Actor* pOwner, int pDrawOrder)
    : RenderComponent(pOwner), mDrawOrder(pDrawOrder)
{
}

void ScreenEffectRenderComponent::Render(IRenderer* pRenderer)
{
    if (mShaderProgram.GetID() == 0)
    {
        return;
    }

    pRenderer->DrawScreenEffect(mShaderProgram);
}

RenderType ScreenEffectRenderComponent::GetRenderType()
{
    return RenderType::Viewport;
}

ShaderProgram& ScreenEffectRenderComponent::GetShaderProgram()
{
    return mShaderProgram;
}

int ScreenEffectRenderComponent::GetDrawOrder() const
{
    return mDrawOrder;
}
