#pragma once

#include <string>
#include <fstream>

//TODO : add description for this enum
enum ShaderType
{
	VERTEX,
	FRAGMENT,
	TESSELLATION_CONTROL,
	TESSELLATION_EVALUATION,
	GEOMETRY
};

/*
Shader is a class representing a shader in OpenGL. 
It handles the creation, loading, and compilation of shaders from files, 
including vertex, fragment, tessellation control, tessellation evaluation, and geometry shaders. 
It provides functionality to retrieve the shader ID and its source code.
*/
class Shader
{
public:
	/*
	Default constructor for Shader.
	Initializes shader ID to 0, shader code to an empty string, and type to VERTEX.
	*/
	Shader();
	/*
	Constructor for Shader with provided ID, file name, and shader type.
	@param pId The ID of the shader.
	@param pFile The source code of the shader in string format.
	@param pShaderType The type of the shader (e.g., vertex, fragment).
	*/
	Shader(int pId, std::string pFile, ShaderType pShaderType);
	/*
	Destructor for Shader.
	Cleans up any allocated resources.
	*/
	~Shader() {};

	/*
	Gets the shader ID.
	@return The ID of the shader.
	*/
	int GetID() const;
	/*
	Gets the shader type.
	@return The type of the shader.
	*/
	ShaderType GetType() const;

	/*
	Loads the shader code from the specified file and sets the shader type.
	@param pFileName The name of the shader file to load.
	@param pShaderType The type of the shader (e.g., vertex, fragment).
	*/
	void Load(std::string pFileName, ShaderType pShaderType);

	/*
	The path to the shader files.
	Feel free to adjust if needed.
	*/
	static const std::string SHADER_PATH;

	/*
	Gets the shader code. (contents of the text file)
	@return A reference to the shader source code.
	*/
	std::string& GetCode();

protected: 
	unsigned int mId; // The OpenGL shader ID.
	std::string mCode; // The source code of the shader.
	ShaderType mType; // The type of the shader (vertex, fragment, etc.).
};

