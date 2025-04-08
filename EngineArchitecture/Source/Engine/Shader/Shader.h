#pragma once

#include <string>
#include <fstream>

enum ShaderType
{
	VERTEX,
	FRAGMENT,
	TESSELLATION_CONTROL,
	TESSELLATION_EVALUATION,
	GEOMETRY
};

class Shader
{
public:
	Shader();
	Shader(int pId, std::string pFile, ShaderType pShaderType);
	~Shader() {};

	int GetID() const;
	ShaderType GetType() const;
	void Load(std::string pFileName, ShaderType pShaderType);

	//Feel free to change the shader path  if needed
	static const std::string SHADER_PATH;

	//Contents of the text file
	std::string& GetCode();

protected:
	unsigned int mId;
	std::string mCode;
	ShaderType mType;
};

