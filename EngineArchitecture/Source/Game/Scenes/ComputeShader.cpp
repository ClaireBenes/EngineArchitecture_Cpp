#include "ComputeShader.h"

#include "Engine/Renderer/RendererGL.h"
#include "Engine/Manager/AssetManager.h"

#include "Engine/GameTool/Movement/Controller/EditorController.h"
#include "Engine/GameTool/Camera.h"

void ComputeShader::Load()
{
    // Need this to use gl_PointSize in vertex shader
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
    float distX = static_cast<float>(GridWidth) / static_cast<float>(VerticesCountX - 1);
    float distY = static_cast<float>(GridHeight) / static_cast<float>(VerticesCountY - 1);

    for(int y = 0; y < VerticesCountY; y++)
    {
        for(int x = 0; x < VerticesCountX; x++)
        {
            mVertices.push_back(Vector4(x * distX, 0, -y * distY, 1));
        }
    }

    printf("Vertices Count: %d\n", mVertices.size());

    // Setup rest lengths
    mComputeShader.Use();
    mComputeShader.setFloat("uDesiredHorizontalLength", distX);
    mComputeShader.setFloat("uDesiredVerticalLength", distY);
    mComputeShader.setFloat("uDesiredDiagonalLength", sqrtf(distX * distX + distY * distY));

    //Generate double buffers
    for (int i = 0; i < 2; i++)
    {
        glGenBuffers(1, &mPositionBuffers[i]);
        glGenBuffers(1, &mVelocityBuffers[i]);
    }

    //Bind all buffers
    //Position
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, mPositionBuffers[0]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, mVertices.size() * sizeof(Vector4), mVertices.data(), GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, mPositionBuffers[1]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, mVertices.size() * sizeof(Vector4), nullptr, GL_STATIC_DRAW);

    //Velocity
    std::vector<Vector4> velocities(mVertices.size(), Vector4::ZERO);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, mVelocityBuffers[0]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, velocities.size() * sizeof(Vector4), velocities.data(), GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, mVelocityBuffers[1]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, velocities.size() * sizeof(Vector4), nullptr, GL_STATIC_DRAW);

    //Vertex Array
    //Generate VAO
    glGenVertexArrays(1, &mVertexArrayId);
    glBindVertexArray(mVertexArrayId);

    //Position
    glBindBuffer(GL_ARRAY_BUFFER, mPositionBuffers[0]);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vector4), (void*) 0);
    glEnableVertexAttribArray(0);

    //Velocity
    glBindBuffer(GL_ARRAY_BUFFER, mVelocityBuffers[0]);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vector4), (void*) 0);
    glEnableVertexAttribArray(1);

    //Unbind VAO
    glBindVertexArray(0);
}

void ComputeShader::Start()
{
    SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    mCamera = new Camera();
    AddActor(mCamera);
    mCamera->mTransform->mPosition = { GridWidth * 0.5f, GridHeight * 0.1f, -30 };
    mCamera->mTransform->RotatePitch(25);

    mMoveComponent = new EditorController(mCamera);
}

void ComputeShader::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void ComputeShader::Draw()
{
    Vector3 windForce = Vector3(cosf(Time::GetGameTime() * 0.5f) * 20.0f, 0, sinf(Time::GetGameTime()) * 10.0f);

    mComputeShader.Use();
    mComputeShader.setVector3f("uWindForce", windForce);

    int iterations = std::min(60 / Time::deltaTime, 3000.0f);

    for(int i = 0; i < iterations; i++)
    {
        // Compute shader
        glDispatchCompute(VerticesCountX / 10, VerticesCountY / 10, 1);
        glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT | GL_SHADER_STORAGE_BARRIER_BIT);

        // Swap buffers
        mDoubleBufferIndex = 1 - mDoubleBufferIndex;  // 0 --> 1 --> 0 --> ...
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, mPositionBuffers[mDoubleBufferIndex]);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, mPositionBuffers[1 - mDoubleBufferIndex]);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, mVelocityBuffers[mDoubleBufferIndex]);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, mVelocityBuffers[1 - mDoubleBufferIndex]);
    }

    // Render shader
    mRenderShader.Use();
    mRenderShader.setMatrix4("uWorldTransform", Matrix4::Identity);
    mRenderShader.setMatrix4("uViewProj", GetRenderer()->GetViewMatrix() * GetRenderer()->GetProjectionMatrix());
    glBindVertexArray(mVertexArrayId);
    glDrawArrays(GL_POINTS, 0, mVertices.size());
}
