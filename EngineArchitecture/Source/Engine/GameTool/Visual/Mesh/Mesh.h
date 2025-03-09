#pragma once

#include "../Texture.h"
#include "Engine/Shader/ShaderProgram.h"

#include <vector>

class VertexArray;
class ShaderProgram;

class Mesh
{
public:
	Mesh();
	Mesh(VertexArray* pVao, ShaderProgram pShaderProgram);

	void Unload();
	void AddTexture(Texture* pTexture);

	//Getters & Setters
	Texture* GetTexture(int index);
	ShaderProgram GetShaderProgram();
	VertexArray* GetVertexArray();

	void SetShaderProgram(ShaderProgram pShaderProgram);
	void SetVertexArray(VertexArray* pVao);

private:
	std::vector<Texture*> mAllTextures;
	VertexArray* mVao = nullptr;

	ShaderProgram mMeshShaderProgram;
};

