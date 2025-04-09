#include "RendererGL.h"

#include "Engine/GameTool/Actor.h"
#include "Engine/GameTool/Utility/Matrix/Matrix4.h"
#include "Engine/GameTool/Visual/Render/Sprite/SpriteRenderComponent.h"
#include "Engine/GameTool/Visual/Mesh/MeshComponent.h"
#include "Engine/GameTool/Visual/Mesh/Mesh.h"
#include "Engine/Manager/AssetManager.h"
#include "Engine/Renderer/DebugRenderInterface.h"
#include "Engine/Engine.h"

#include <SDL_image.h>
#include <glew.h>

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

Mesh* RendererGL::mCubeMesh = nullptr;
ShaderProgram RendererGL::mSimpleMeshShaderProgram = ShaderProgram();
ShaderProgram RendererGL::mTesselationMeshShaderProgram = ShaderProgram();
ShaderProgram RendererGL::mGrassShaderProgram = ShaderProgram();

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

    // TODO: To move in its own LoadMeshes function
    mCubeMesh = AssetManager::LoadMesh("cube.obj", "engineCube");
    mCubeMesh->SetShaderProgram(mSimpleMeshShaderProgram);
    mCubeMesh->AddTexture(AssetManager::LoadTexture(*this, "Resources/Textures/wall.jpg", "engineGround"));

    return true;
}

void RendererGL::LoadShaders()
{
    //Sprite 
    Shader spriteVertexShader = Shader();
    Shader spriteFragShader = Shader();

    spriteVertexShader.Load("Simple.vert", ShaderType::VERTEX);
    spriteFragShader.Load("Simple.frag", ShaderType::FRAGMENT);

    mSpriteShaderProgram.Compose({ &spriteVertexShader,&spriteFragShader });
    mSpriteShaderProgram.setMatrix4("uViewProj", mSpriteViewProj);

    //Rect 
    Shader rectVertexShader = Shader();
    Shader rectFragShader = Shader();

    rectVertexShader.Load("Simple.vert", ShaderType::VERTEX);
    rectFragShader.Load("Simple.frag", ShaderType::FRAGMENT);

    mRectShaderProgram.Compose({ &rectVertexShader,&rectFragShader });

    //RectLine 
    Shader rectLineVertexShader = Shader();
    Shader rectLineFragShader = Shader();

    rectLineVertexShader.Load("Simple.vert", ShaderType::VERTEX);
    rectLineFragShader.Load("Simple.frag", ShaderType::FRAGMENT);

    mRectLineShaderProgram.Compose({ &rectLineVertexShader,&rectLineFragShader });

    //Mesh
    Shader simpleMeshVertexShader = Shader();
    Shader simpleMeshFragShader = Shader();

    simpleMeshVertexShader.Load("SimpleMesh.vert", ShaderType::VERTEX);
    simpleMeshFragShader.Load("SimpleMesh.frag", ShaderType::FRAGMENT);

    mSimpleMeshShaderProgram.Compose({ &simpleMeshVertexShader, &simpleMeshFragShader });

    //Tesselation Mesh
    Shader tesselationMeshVertexShader = Shader();
    Shader tesselationMeshFragShader = Shader();
    Shader tesselationControlShader = Shader();
    Shader tesselationEvaluationShader = Shader();

    tesselationMeshVertexShader.Load("TesselationMesh.vert", ShaderType::VERTEX);
    tesselationMeshFragShader.Load("TesselationMesh.frag", ShaderType::FRAGMENT);
    tesselationControlShader.Load("Simple.tesc", ShaderType::TESSELLATION_CONTROL);
    tesselationEvaluationShader.Load("Simple.tese", ShaderType::TESSELLATION_EVALUATION);

    mTesselationMeshShaderProgram.Compose({ &tesselationMeshVertexShader, &tesselationControlShader, &tesselationEvaluationShader, &tesselationMeshFragShader });

    //Terrain
    Shader terrainVertexShader = Shader();
    Shader terrainFragShader = Shader();
    Shader terrainControlShader = Shader();
    Shader terrainEvaluationShader = Shader();

    terrainVertexShader.Load("Terrain.vert", ShaderType::VERTEX);
    terrainFragShader.Load("Terrain.frag", ShaderType::FRAGMENT);
    terrainControlShader.Load("Terrain.tesc", ShaderType::TESSELLATION_CONTROL);
    terrainEvaluationShader.Load("Terrain.tese", ShaderType::TESSELLATION_EVALUATION);

    mTerrainShaderProgram.Compose({ &terrainVertexShader, &terrainControlShader, &terrainEvaluationShader, &terrainFragShader });

    //Grass
    Shader grassVertexShader = Shader();
    Shader grassFragShader = Shader();

    grassVertexShader.Load("Grass.vert", ShaderType::VERTEX);
    grassFragShader.Load("Grass.frag", ShaderType::FRAGMENT);

    mGrassShaderProgram.Compose({ &grassVertexShader, &grassFragShader });
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

    if (Engine::mInDebugMode)
    {
        for (DebugRenderInterface* debugRender : mDebugRenders)
        {
            debugRender->DebugRender(this);
        }
    }

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

void RendererGL::DrawSprite(const Actor& rOwner, Texture* rTexture, Rectangle rec, Flip flip)
{
    mSpriteShaderProgram.Use();

    Matrix4 screen = Matrix4::CreateScale(
        rec.dimensions.x,
        rec.dimensions.y,
        0.0f);

    screen *= Matrix4::CreateTranslation(Vector3(
        rec.position.x,
        rec.position.y,
        0.0f));

    mSpriteShaderProgram.setMatrix4("uWorldTransform", screen);
    rTexture->SetActive();
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

    //TODO : Choose to see or not inside faces (by enabling GL_CULL_FACE)
    //glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    for (RenderComponent* rc : mWorldRenderComponents)
    {
        rc->Render(this);
    }
}

void RendererGL::DrawMesh(Mesh* pMesh, int pTextureIndex, const Matrix4& transform, Vector2 tiling)
{
    if (pMesh)
    {
        pMesh->GetShaderProgram().Use();
        pMesh->GetShaderProgram().setMatrix4("uViewProj", mView * mProjection);
        pMesh->GetShaderProgram().setMatrix4("uWorldTransform", transform);
        pMesh->GetShaderProgram().setFloat("time", Time::GetGameTime());
        pMesh->GetShaderProgram().setVector2f("uTileSize", tiling);

        Texture* t = pMesh->GetTexture(pTextureIndex);
        if (t)
        {
            t->SetActive();
        }

        pMesh->GetVertexArray()->SetActive();


        glDrawArraysInstanced(GL_TRIANGLES, 0, pMesh->GetVertexArray()->GetVerticeCount(), 10 * 10);
        //glDrawArrays(pMesh->GetShaderProgram().GetTesselation() ? GL_PATCHES : GL_TRIANGLES, 0, pMesh->GetVertexArray()->GetVerticeCount());
        glLineWidth(2);
        glPolygonMode(GL_FRONT_AND_BACK, Engine::mInWireframeMode ? GL_LINE : GL_FILL);
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

Mesh* RendererGL::GetCubeMesh()
{
    return mCubeMesh;
}
