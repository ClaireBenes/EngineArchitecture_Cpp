#pragma once

#include "../Texture.h"
#include "Engine/Shader/ShaderProgram.h"


#include "Engine/Vertex/Vertex.h"

#include <vector>

class VertexArray;
class ShaderProgram;

class Mesh
{
public:
	Mesh();
	Mesh(const std::vector<Vertex>& pVertices);

	void Unload();
	void AddTexture(Texture* pTexture);

	float* ToVerticeArray();

	//Getters & Setters
	Texture* GetTexture(int index);
	ShaderProgram GetShaderProgram();
	VertexArray* GetVertexArray();

	void SetShaderProgram(ShaderProgram pShaderProgram);
	void SetVertexArray(VertexArray* pVao);

private:
	std::vector<Texture*> mAllTextures;
	VertexArray* mVao = nullptr;

	std::vector<Vertex> mVertices;

	ShaderProgram mMeshShaderProgram;
};

