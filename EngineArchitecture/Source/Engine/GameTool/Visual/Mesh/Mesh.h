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
	VertexArray* mVao;

	//SHADERS
	Shader mMeshFragShader;
	Shader mMeshVertexShader;

	ShaderProgram mMeshShaderProgram;

};

