#pragma once

#include <string>
#include <fstream>

/**
 * @brief Types of shaders used in the rendering pipeline.
 */
enum ShaderType
{
	VERTEX,
	FRAGMENT,
	TESSELLATION_CONTROL,
	TESSELLATION_EVALUATION,
	GEOMETRY,
	COMPUTE,
};

/**
 * @brief Shader is a class representing a shader in OpenGL.
 * It handles the creation, loading, and compilation of shaders from files, 
 * including vertex, fragment, tessellation control, tessellation evaluation, and geometry shaders. 
 * It provides functionality to retrieve the shader ID and its source code.
*/
class Shader
{
public:
	/**
	 * @brief Default constructor for Shader.
	 * Initializes shader ID to 0, shader code to an empty string, and type to VERTEX.
	 */
	Shader();
	/**
	 * @brief Constructor for Shader with provided ID, file name, and shader type.
	 * @param pId The ID of the shader.
	 * @param pFile The source code of the shader in string format.
	 * @param pShaderType The type of the shader (e.g., vertex, fragment).
	 */
	Shader(int pId, std::string pFile, ShaderType pShaderType);
	/**
	 * @brief Destructor for Shader.
	 * Cleans up any allocated resources.
	 */
	~Shader() {};

	/**
	 * @brief Gets the shader ID.
	 * @return The ID of the shader.
	 */
	int GetID() const;
	/**
	 * @brief Gets the shader type.
	 * @return The type of the shader.
	 */
	ShaderType GetType() const;

	/**
	 * @brief Loads the shader code from the specified file and sets the shader type.
	 * @param pFileName The name of the shader file to load.
	 * @param pShaderType The type of the shader (e.g., vertex, fragment).
	 */
	void Load(std::string pFileName, ShaderType pShaderType);

	/**
	 * @brief The path to the shader files.
	 * Feel free to adjust if needed.
	 */
	static const std::string SHADER_PATH;

	/**
	 * @brief Gets the shader code. (contents of the text file)
	 * @return A reference to the shader source code.
	 */
	std::string& GetCode();

protected: 
	/**
	 * @brief The OpenGL shader ID.
	 */
	unsigned int mId;
	/**
	 * @brief The source code of the shader.
	 */
	std::string mCode;
	/**
	 * @brief The type of the shader (vertex, fragment, etc.).
	 */
	ShaderType mType;
};

