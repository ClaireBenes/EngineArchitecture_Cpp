#include "ComputeShader.h"

#include "Engine/Renderer/RendererGL.h"
#include "Engine/Manager/AssetManager.h"

#include "Engine/GameTool/Movement/Controller/EditorController.h"
#include "Engine/GameTool/Camera.h"

#include "Game/Actors/Floor.h"

void ComputeShader::Load()
{
    //  I need to enable this to use gl_PointSize in my vertex shader
    glEnable(GL_PROGRAM_POINT_SIZE);

    //Compute shader
    Shader clothComputeShader = Shader();

    clothComputeShader.Load("Cloth.comp", ShaderType::COMPUTE);

    mComputeShader.Compose({ &clothComputeShader });

    //Render shader
    Shader clothVertexShader = Shader();
    Shader clothFragmentShader = Shader();

    clothVertexShader.Load("Cloth.vert", ShaderType::VERTEX);
    clothFragmentShader.Load("Cloth.frag", ShaderType::FRAGMENT);

    mRenderShader.Compose({ &clothVertexShader, &clothFragmentShader });

    //Vertices
    for(int y = 0; y < VerticesCountY; y++)
    {
        for(int x = 0; x < VerticesCountX; x++)
        {
            mVertices.push_back(Vector3(x * GridWidth / VerticesCountX, 0, y * GridHeight / VerticesCountY));
        }
    }

    //Vertex Array
    //Generate VAO
    glGenVertexArrays(1, &mVertexArrayId);
    glBindVertexArray(mVertexArrayId);

    //Generate VBO
    glGenBuffers(1, &mVertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);

    //Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*) 0);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, mVertexBufferId);
    glBufferData(GL_SHADER_STORAGE_BUFFER, mVertices.size() * 3 * sizeof(float), mVertices.data(), GL_STATIC_DRAW);

    //Floor
    Mesh* floorMesh = AssetManager::LoadMesh("cube.obj", "cube");
    floorMesh->SetShaderProgram(RendererGL::mSimpleMeshShaderProgram);

    AssetManager::LoadTexture(*GetRenderer(), "Resources/Textures/grass.png", "floor");
    floorMesh->AddTexture(AssetManager::GetTexture("floor"));
}

void ComputeShader::Start()
{
    SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    /*Floor* floor = new Floor();
    AddActor(floor);
    floor->mTransform->mScale = Vector3(50, 0.01f, 50);
    floor->mTransform->mPosition = { 0, -2.5f, 35 };*/

    mCamera = new Camera();
    AddActor(mCamera);
    mCamera->mTransform->mPosition = { 25, 10, -50 };

    mMoveComponent = new EditorController(mCamera);
}

void ComputeShader::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void ComputeShader::Draw()
{
    mComputeShader.Use();
    glDispatchCompute(VerticesCountX / 10, VerticesCountY / 10, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    mRenderShader.Use();
    mRenderShader.setMatrix4("uWorldTransform", Matrix4::Identity);
    mRenderShader.setMatrix4("uViewProj", GetRenderer()->GetViewMatrix() * GetRenderer()->GetProjectionMatrix());
    glBindVertexArray(mVertexArrayId);
    glDrawArrays(GL_POINTS, 0, mVertices.size());
}
