#pragma once

#include "Shader.h"

#include "Engine/GameTool/Utility/Vector/Vector2.h"
#include "Engine/GameTool/Utility/Vector/Vector3.h"
#include "Engine/GameTool/Utility/Vector/Vector4.h"
#include "Engine/GameTool/Utility/Matrix/Matrix4.h"

#include <vector>
#include <glew.h>

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram() = default;
	void Unload();
	void Compose(std::vector<Shader*> shaders);

	unsigned int GetID();
	bool GetTesselation();
	void Use();

	void setFloat(const GLchar* name, GLfloat value);
	void setInteger(const GLchar* name, GLint value);
	void setVector2f(const GLchar* name, GLfloat x, GLfloat y);
	void setVector2f(const GLchar* name, const Vector2& value);
	void setVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z);
	void setVector3f(const GLchar* name, const Vector3& value);
	void setVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void setVector4f(const GLchar* name, const Vector4& value);
	void setMatrix4(const GLchar* name, const Matrix4& matrix);

private:
	unsigned int mId;
	bool mHasTesselation = false;
};


