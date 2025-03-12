#include "RendererGL.h"

#include "Engine/GameTool/Actor.h"
#include "Engine/GameTool/Utility/Matrix/Matrix4.h"
#include "Engine/GameTool/Visual/Render/Sprite/SpriteRenderComponent.h"
#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"
#include "Engine/GameTool/Visual/Mesh/Mesh.h"
#include "Engine/Manager/AssetManager.h"

#include <SDL_image.h>
#include <glew.h>

constexpr float cubeVertices[] = {
    // Positions           // Coordonnées de texture
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,   // Face avant
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   // Face arrière
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,   // Face gauche
    -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 1.0f,

    0.5f, -0.5f, -0.5f, 0.0f, 0.0f,   // Face droite
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,   // Face bas
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 1.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f,   // Face haut
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f
};

constexpr unsigned int cubeIndices[] = {
    0, 2, 1, 1, 2, 3,  // Face avant
    4, 5, 6, 5, 7, 6,  // Face arrière
    8, 9, 10, 9, 11, 10, // Face gauche
    12, 13, 14, 13, 15, 14, // Face droite
    16, 17, 18, 17, 19, 18, // Face bas
    20, 21, 22, 21, 23, 22  // Face haut
};

constexpr float spriteVertices[] = {
    //POSITION                   NORMALS                    TEXCOORDS
    -0.5f, 0.5f, 0.0f,           0.0f, 0.0f, 0.0f,          0.0f, 0.0f,     //top left
    0.5f, 0.5f, 0.0f,            0.0f, 0.0f, 0.0f,          1.0f, 0.0f,     //top right
    -0.5f, -0.5f, 0.0f,          0.0f, 0.0f, 0.0f,          0.0f, 1.0f,      //bottom left
    0.5f, -0.5f, 0.0f,           0.0f, 0.0f, 0.0f,          1.0f, 1.0f,     //bottom right

};   

constexpr unsigned int spriteIndices[] = {
    0, 1, 2,
    2, 3, 0
};

Mesh* RendererGL::CubeMesh = nullptr;

RendererGL::RendererGL() : mWindow(nullptr), mSpriteVao(nullptr), mContext(nullptr)
{
}

RendererGL::~RendererGL()
{
    delete mSpriteVao;
    delete CubeMesh;
}

bool RendererGL::Initialize(Window& rWindow)
{
    mWindow = &rWindow;

    mSpriteViewProj = Matrix4::CreateSimpleViewProj(mWindow->GetDimensions().x, mWindow->GetDimensions().y);
    mView = Matrix4::CreateLookAt(Vector3(0, 0, 10), Vector3::Zero, Vector3::Up);
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

    mSpriteVao = new VertexArray(spriteVertices, 4);
    LoadShaders();

    CubeMesh = AssetManager::LoadMesh("cube.obj","cube");
    CubeMesh->SetShaderProgram(mSimpleMeshShaderProgram);

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

    //Mesh
    mSimpleMeshVertexShader.Load("SimpleMesh.vert", ShaderType::VERTEX);
    mSimpleMeshFragShader.Load("SimpleMesh.frag", ShaderType::FRAGMENT);

    mSimpleMeshShaderProgram.Compose({ &mSimpleMeshVertexShader, &mSimpleMeshFragShader });
}

void RendererGL::BeginDraw()
{
    glClearColor(0.45f, 0.45f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mSpriteVao->SetActive();
}

void RendererGL::Draw()
{
    DrawAllMeshes();
    DrawAllSprites();
}

void RendererGL::EndDraw()
{
    SDL_GL_SwapWindow(mWindow->GetSdlWindow());
}

void RendererGL::DrawAllSprites()
{
    glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    mSpriteShaderProgram.Use();
    mSpriteShaderProgram.setMatrix4("uViewProj", mSpriteViewProj);
    mSpriteVao->SetActive();

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
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
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

    // TODO: Cull faces when you have an actual .obj model importer
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);

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
        //glDrawElements(GL_TRIANGLES, pMesh->GetVertexArray()->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
        glDrawArrays(GL_TRIANGLES, 0, pMesh->GetVertexArray()->GetVerticeCount());

    }

    //Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void RendererGL::SetViewMatrix(const Matrix4& pView)
{
    mView = pView;
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
