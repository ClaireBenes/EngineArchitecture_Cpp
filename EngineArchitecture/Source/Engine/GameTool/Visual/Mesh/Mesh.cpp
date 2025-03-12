#include "Mesh.h"

#include "Engine/Vertex/VertexArray.h"
#include "Engine/Manager/AssetManager.h"

Mesh::Mesh()
{
}

Mesh::Mesh(const std::vector<Vertex>& pVertices):
	mVertices(pVertices)
{
	float* verticeArray = ToVerticeArray();
	mVao = new VertexArray(verticeArray, mVertices.size());
	delete[] verticeArray;
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

float* Mesh::ToVerticeArray()
{
	float* array = new float[mVertices.size() * 8];
	int counter = 0;
	for (int i = 0; i < mVertices.size(); i++)
	{
		array[counter + 0] = mVertices[i].position.x;
		array[counter + 1] = mVertices[i].position.y;
		array[counter + 2] = mVertices[i].position.z;
		array[counter + 3] = mVertices[i].normal.x;
		array[counter + 4] = mVertices[i].normal.y;
		array[counter + 5] = mVertices[i].normal.z;
		array[counter + 6] = mVertices[i].uv.x;
		array[counter + 7] = mVertices[i].uv.y;
		counter += 8;
	}
	return array;
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
