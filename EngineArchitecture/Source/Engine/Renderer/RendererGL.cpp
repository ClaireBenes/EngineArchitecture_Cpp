#include "RendererGL.h"

#include "Engine/GameTool/Actor.h"
#include "Engine/GameTool/Utility/Matrix/Matrix4.h"
#include "Engine/GameTool/Visual/Render/Sprite/SpriteRenderComponent.h"
#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"
#include "Engine/GameTool/Visual/Mesh/Mesh.h"

#include <SDL_image.h>
#include <glew.h>

RendererGL::RendererGL() : mWindow(nullptr), mSpriteVao(nullptr), mContext(nullptr)
{
}

RendererGL::~RendererGL()
{
    delete mSpriteVao;
}

bool RendererGL::Initialize(Window& rWindow)
{
    mWindow = &rWindow;

    mSpriteViewProj = Matrix4::CreateSimpleViewProj(mWindow->GetDimensions().x, mWindow->GetDimensions().y);
    mView = Matrix4::CreateLookAt(Vector3(0, 0, 5), Vector3::Right, Vector3::Forward);
    mProjection = Matrix4::CreatePerspectiveFOV(70.0f, mWindow->GetDimensions().x, mWindow->GetDimensions().y, 0.01f, 10000.0f);

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

    mSpriteVao = new VertexArray(vertices, 4, indices, 6);
    LoadShaders();

    return true;
}

void RendererGL::LoadShaders()
{
    //Sprite 
    mSpriteVertexShader.Load("Simple.vert", ShaderType::VERTEX);
    mSpriteFragShader.Load("Simple.frag", ShaderType::FRAGMENT);

    mSpriteShaderProgram.Compose({ &mSpriteVertexShader,&mSpriteFragShader });
    mSpriteShaderProgram.setMatrix4("uViewProj", mSpriteViewProj);

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    mSpriteVao->SetActive();
}

void RendererGL::Draw()
{
    //DrawAllMeshes();
    DrawAllSprites();
}

void RendererGL::EndDraw()
{
    SDL_GL_SwapWindow(mWindow->GetSdlWindow());
}

void RendererGL::DrawAllSprites()
{
    for (RenderComponent* rc : mViewportRenderComponents)
    {
        rc->Render(this);
    }
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

void RendererGL::DrawAllMeshes()
{
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    for (RenderComponent* rc : mWorldRenderComponents)
    {
        rc->Render(this);
    }
}

void RendererGL::DrawMesh(Mesh* pMesh, int pTextureIndex, const Matrix4& transform)
{
    if (pMesh)
    {
        pMesh->GetShaderProgram().Use();
        pMesh->GetShaderProgram().setMatrix4("uViewProj", mView * mProjection);
        pMesh->GetShaderProgram().setMatrix4("uWorldTransform", transform);

        Texture* t = pMesh->GetTexture(pTextureIndex);
        if (t)
        {
            t->SetActive();
        }

        pMesh->GetVertexArray()->SetActive();
        glDrawElements(GL_TRIANGLES, pMesh->GetVertexArray()->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
    }
}

void RendererGL::Close()
{
    SDL_GL_DeleteContext(mContext);
    delete mSpriteVao;
}

IRenderer::RendererType RendererGL::GetType()
{
    return RendererType::OPENGL;
}
