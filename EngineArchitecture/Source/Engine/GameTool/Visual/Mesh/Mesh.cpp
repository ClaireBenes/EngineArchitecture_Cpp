#include "Mesh.h"

#include "Engine/Vertex/VertexArray.h"
#include "Engine/Manager/AssetManager.h"

Mesh::Mesh()
{
}

Mesh::Mesh(VertexArray* pVao, ShaderProgram pShaderProgram):
	mVao(pVao), mMeshShaderProgram(pShaderProgram)
{
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
