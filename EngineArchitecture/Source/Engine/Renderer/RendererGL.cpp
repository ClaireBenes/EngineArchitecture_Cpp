#include "RendererGL.h"

#include "Engine/GameTool/Actor.h"
#include "Engine/GameTool/Utility/Matrix/Matrix4.h"
#include "Engine/GameTool/Visual/Render/Sprite/SpriteRenderComponent.h"

#include <SDL_image.h>
#include <glew.h>

RendererGL::RendererGL() : mWindow(nullptr), mVao(nullptr), mContext(nullptr)
{
}

RendererGL::~RendererGL()
{
    delete mVao;
}

bool RendererGL::Initialize(Window& rWindow)
{
    mWindow = &rWindow;
    mViewProj = Matrix4::CreateSimpleViewProj(mWindow->GetDimensions().x, mWindow->GetDimensions().y);

    //Setting OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    //8 bits color buffer
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    mContext = SDL_GL_CreateContext(mWindow->GetSdlWindow());
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        Log::Error(LogType::Video, "Failed to initialize GLEW");
        return false;
    }
    glGetError();

    if(IMG_Init(IMG_INIT_PNG) == 0)
    {
        Log::Error(LogType::Video, "Failed to initialize SDL_Image");
    }

    mVao = new VertexArray(vertices, 4, indices, 6);
    LoadShaders();

    return true;
}

void RendererGL::LoadShaders()
{
    //Sprite 
    mSpriteVertexShader.Load("Simple.vert", ShaderType::VERTEX);
    mSpriteFragShader.Load("Simple.frag", ShaderType::FRAGMENT);

    mSpriteShaderProgram.Compose({ &mSpriteVertexShader,&mSpriteFragShader });
    mSpriteShaderProgram.setMatrix4("uViewProj", mViewProj);

    //Rect 
    mRectVertexShader.Load("Simple.vert", ShaderType::VERTEX);
    mRectFragShader.Load("Simple.frag", ShaderType::FRAGMENT);

    mRectShaderProgram.Compose({ &mRectVertexShader,&mRectFragShader });

    //RectLine 
    mRectLineVertexShader.Load("Simple.vert", ShaderType::VERTEX);
    mRectLineFragShader.Load("Simple.frag", ShaderType::FRAGMENT);

    mRectLineShaderProgram.Compose({ &mRectLineVertexShader,&mRectLineFragShader });
}

void RendererGL::BeginDraw()
{
    glClearColor(0.45f, 0.45f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    mVao->SetActive();
}

void RendererGL::EndDraw()
{
    SDL_GL_SwapWindow(mWindow->GetSdlWindow());
}

void RendererGL::DrawSprite(const Actor& rOwner, Texture& rTexture, Rectangle rec, Flip flip)
{
    mSpriteShaderProgram.Use();

    rOwner.mTransform->ComputeWorldTransform();
    Matrix4 scaleMat = Matrix4::CreateScale(
        rTexture.GetWidth(),
        rTexture.GetHeight(),
        0.0f);
    Matrix4 world = scaleMat * rOwner.mTransform->GetWorldTransform();
    mSpriteShaderProgram.setMatrix4("uWorldTransform", world);
    rTexture.SetActive();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void RendererGL::DrawRect(const Rectangle& rRect, Color pColor)
{
    mRectShaderProgram.Use();
}

void RendererGL::DrawRectLine(const Rectangle& rRect, Color pColor)
{
    mRectLineShaderProgram.Use();
}

void RendererGL::AddSprite(SpriteRenderComponent* pSprite)
{
    int spriteDrawOrder = pSprite->GetDrawOrder();
    std::vector<SpriteRenderComponent*>::iterator sc;
    for(sc = mSprites.begin(); sc != mSprites.end(); ++sc)
    {
        if(spriteDrawOrder < ( *sc )->GetDrawOrder()) break;
    }
    mSprites.insert(sc, pSprite);
}

void RendererGL::RemoveSprite(SpriteRenderComponent* pSprite)
{
    std::vector<SpriteRenderComponent*>::iterator sc;
    sc = std::find(mSprites.begin(), mSprites.end(), pSprite);
    mSprites.erase(sc);
}

void RendererGL::Close()
{
    SDL_GL_DeleteContext(mContext);
    delete mVao;
}

IRenderer::RendererType RendererGL::GetType()
{
    return RendererType::OPENGL;
}
