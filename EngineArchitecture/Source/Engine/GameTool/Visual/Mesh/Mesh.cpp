#include "Mesh.h"

#include "Engine/Vertex/VertexArray.h"
#include "Engine/Manager/AssetManager.h"

Mesh::Mesh()
{
	mVao = nullptr;
	//mVao = new VertexArray(cubeVertices, 28, cubeIndices, 36);
	//mMeshVertexShader.Load("Simple.vert", ShaderType::VERTEX);
	//mMeshFragShader.Load("Simple.frag", ShaderType::FRAGMENT);
	//mMeshShaderProgram.Compose({ &mMeshVertexShader, &mMeshFragShader });
	//mAllTextures.emplace_back(&AssetManager::GetTexture("wall"));
}

void Mesh::Unload()
{
	delete mVao;
	mVao = nullptr;
}

void Mesh::AddTexture(Texture* pTexture)
{
	mAllTextures.emplace_back(pTexture);
}

Texture* Mesh::GetTexture(int index)
{
	if (index < mAllTextures.size())
	{
		return mAllTextures[index];
	}
	else
	{
		return nullptr;
	}
}

ShaderProgram Mesh::GetShaderProgram()
{
	return mMeshShaderProgram;
}

VertexArray* Mesh::GetVertexArray()
{
	return mVao;
}

void Mesh::SetShaderProgram(ShaderProgram pShaderProgram)
{
	mMeshShaderProgram = pShaderProgram;
}

void Mesh::SetVertexArray(VertexArray* pVao)
{
	mVao = pVao;
}
