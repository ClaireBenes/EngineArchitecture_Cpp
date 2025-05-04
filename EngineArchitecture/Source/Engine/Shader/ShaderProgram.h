#pragma once

#include "Shader.h"

#include "Engine/GameTool/Utility/Vector/Vector2.h"
#include "Engine/GameTool/Utility/Vector/Vector3.h"
#include "Engine/GameTool/Utility/Vector/Vector4.h"
#include "Engine/GameTool/Utility/Matrix/Matrix4.h"

#include <vector>
#include <glew.h>

/*
ShaderProgram is a class that represents an OpenGL shader program. 
It is responsible for managing the compilation, linking, and use of shaders in an OpenGL application.
It allows setting uniforms such as floats, vectors, and matrices, as well as
determining if tessellation shaders are part of the program.
*/
class ShaderProgram
{
public:
	/*
	Default constructor for ShaderProgram.
	Initializes the shader program ID to 0.
	*/
	ShaderProgram();
	/*
	Destructor for ShaderProgram.
	Frees the resources associated with the shader program.
	*/
	~ShaderProgram() = default;

	/*
	Unloads the shader program, deleting it from OpenGL.
	*/
	void Unload();
	/*
	Compiles and links the provided shaders into the shader program.
	@param shaders A vector of Shader objects to be attached and linked into the program.
	*/
	void Compose(std::vector<Shader*> shaders);

	/*
	Gets the ID of the shader program.
	@return The OpenGL ID of the shader program.
	*/
	unsigned int GetID();
	/*
	Checks if the shader program uses tessellation shaders.
	@return True if the shader program has tessellation shaders, otherwise false.
	*/
	bool GetTesselation();
	/*
	Activates the shader program for use in OpenGL rendering.
	*/
	void Use();

	/*
	Sets a float uniform in the shader program.
	@param name The name of the uniform variable.
	@param value The value to set for the uniform variable.
	*/
	void setFloat(const GLchar* name, GLfloat value);
	/*
	Sets an integer uniform in the shader program.
	@param name The name of the uniform variable.
	@param value The value to set for the uniform variable.
	*/
	void setInteger(const GLchar* name, GLint value);
	/*
	Sets a 2D vector uniform in the shader program.
	@param name The name of the uniform variable.
	@param x The x component of the vector.
	@param y The y component of the vector.
	*/
	void setVector2f(const GLchar* name, GLfloat x, GLfloat y);
	/*
	Sets a 2D vector uniform in the shader program.
	@param name The name of the uniform variable.
	@param value The 2D vector to set for the uniform variable.
	*/
	void setVector2f(const GLchar* name, const Vector2& value);
	/*
	Sets a 3D vector uniform in the shader program.
	@param name The name of the uniform variable.
	@param x The x component of the vector.
	@param y The y component of the vector.
	@param z The z component of the vector.
	*/
	void setVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z);
	/*
	Sets a 3D vector uniform in the shader program.
	@param name The name of the uniform variable.
	@param value The 3D vector to set for the uniform variable.
	*/
	void setVector3f(const GLchar* name, const Vector3& value);
	/*
	Sets a 4D vector uniform in the shader program.
	@param name The name of the uniform variable.
	@param x The x component of the vector.
	@param y The y component of the vector.
	@param z The z component of the vector.
	@param w The w component of the vector.
	*/
	void setVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	/*
	Sets a 4D vector uniform in the shader program.
	@param name The name of the uniform variable.
	@param value The 4D vector to set for the uniform variable.
	*/
	void setVector4f(const GLchar* name, const Vector4& value);
	/*
	Sets a 4x4 matrix uniform in the shader program.
	@param name The name of the uniform variable.
	@param matrix The matrix to set for the uniform variable.
	*/
	void setMatrix4(const GLchar* name, const Matrix4& matrix);

private: 
	unsigned int mId; // The OpenGL ID of the shader program.
	bool mHasTesselation = false; // Whether the shader program uses tessellation shaders.
};


