#pragma once

#include "Engine/GameTool/Utility/Vector/Vector3.h"
#include "Engine/GameTool/Utility/Quaternion/Quaternion.h"

#include <memory.h>

// Row major order 4*4 matrix
class Matrix4
{
public:
	float mat[4][4];

	Matrix4()
	{
		*this = Matrix4::Identity;
	}

	explicit Matrix4(float inMat[4][4])
	{
		memcpy(mat, inMat, 16 * sizeof(float));

	}

	// Cast to a const float pointer
	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&mat[0][0]);
	}

	// Matrix multiplication (a * b)
	friend Matrix4 operator*(const Matrix4& a, const Matrix4& b)
	{
		Matrix4 retVal;
		// row 0
		retVal.mat[0][0] =
			a.mat[0][0] * b.mat[0][0] +
			a.mat[0][1] * b.mat[1][0] +
			a.mat[0][2] * b.mat[2][0] +
			a.mat[0][3] * b.mat[3][0];

		retVal.mat[0][1] =
			a.mat[0][0] * b.mat[0][1] +
			a.mat[0][1] * b.mat[1][1] +
			a.mat[0][2] * b.mat[2][1] +
			a.mat[0][3] * b.mat[3][1];

		retVal.mat[0][2] =
			a.mat[0][0] * b.mat[0][2] +
			a.mat[0][1] * b.mat[1][2] +
			a.mat[0][2] * b.mat[2][2] +
			a.mat[0][3] * b.mat[3][2];

		retVal.mat[0][3] =
			a.mat[0][0] * b.mat[0][3] +
			a.mat[0][1] * b.mat[1][3] +
			a.mat[0][2] * b.mat[2][3] +
			a.mat[0][3] * b.mat[3][3];

		// row 1
		retVal.mat[1][0] =
			a.mat[1][0] * b.mat[0][0] +
			a.mat[1][1] * b.mat[1][0] +
			a.mat[1][2] * b.mat[2][0] +
			a.mat[1][3] * b.mat[3][0];

		retVal.mat[1][1] =
			a.mat[1][0] * b.mat[0][1] +
			a.mat[1][1] * b.mat[1][1] +
			a.mat[1][2] * b.mat[2][1] +
			a.mat[1][3] * b.mat[3][1];

		retVal.mat[1][2] =
			a.mat[1][0] * b.mat[0][2] +
			a.mat[1][1] * b.mat[1][2] +
			a.mat[1][2] * b.mat[2][2] +
			a.mat[1][3] * b.mat[3][2];

		retVal.mat[1][3] =
			a.mat[1][0] * b.mat[0][3] +
			a.mat[1][1] * b.mat[1][3] +
			a.mat[1][2] * b.mat[2][3] +
			a.mat[1][3] * b.mat[3][3];

		// row 2
		retVal.mat[2][0] =
			a.mat[2][0] * b.mat[0][0] +
			a.mat[2][1] * b.mat[1][0] +
			a.mat[2][2] * b.mat[2][0] +
			a.mat[2][3] * b.mat[3][0];

		retVal.mat[2][1] =
			a.mat[2][0] * b.mat[0][1] +
			a.mat[2][1] * b.mat[1][1] +
			a.mat[2][2] * b.mat[2][1] +
			a.mat[2][3] * b.mat[3][1];

		retVal.mat[2][2] =
			a.mat[2][0] * b.mat[0][2] +
			a.mat[2][1] * b.mat[1][2] +
			a.mat[2][2] * b.mat[2][2] +
			a.mat[2][3] * b.mat[3][2];

		retVal.mat[2][3] =
			a.mat[2][0] * b.mat[0][3] +
			a.mat[2][1] * b.mat[1][3] +
			a.mat[2][2] * b.mat[2][3] +
			a.mat[2][3] * b.mat[3][3];

		// row 3
		retVal.mat[3][0] =
			a.mat[3][0] * b.mat[0][0] +
			a.mat[3][1] * b.mat[1][0] +
			a.mat[3][2] * b.mat[2][0] +
			a.mat[3][3] * b.mat[3][0];

		retVal.mat[3][1] =
			a.mat[3][0] * b.mat[0][1] +
			a.mat[3][1] * b.mat[1][1] +
			a.mat[3][2] * b.mat[2][1] +
			a.mat[3][3] * b.mat[3][1];

		retVal.mat[3][2] =
			a.mat[3][0] * b.mat[0][2] +
			a.mat[3][1] * b.mat[1][2] +
			a.mat[3][2] * b.mat[2][2] +
			a.mat[3][3] * b.mat[3][2];

		retVal.mat[3][3] =
			a.mat[3][0] * b.mat[0][3] +
			a.mat[3][1] * b.mat[1][3] +
			a.mat[3][2] * b.mat[2][3] +
			a.mat[3][3] * b.mat[3][3];

		return retVal;
	}

	Matrix4& operator*=(const Matrix4& right)
	{
		*this = *this * right;
		return *this;
	}

	// Invert the matrix - super slow
	void Invert();

	Vector3 GetTranslation() const
	{
		return Vector3(mat[3][0], mat[3][1], mat[3][2]);
	}

	Vector3 GetXAxis() const
	{
		return Vector3::Normalize(Vector3(mat[0][0], mat[0][1], mat[0][2]));
	}

	Vector3 GetYAxis() const
	{
		return Vector3::Normalize(Vector3(mat[1][0], mat[1][1], mat[1][2]));
	}

	Vector3 GetZAxis() const
	{
		return Vector3::Normalize(Vector3(mat[2][0], mat[2][1], mat[2][2]));
	}

	Vector3 GetScale() const
	{
		Vector3 retVal;
		retVal.x = Vector3(mat[0][0], mat[0][1], mat[0][2]).Magnitude();
		retVal.y = Vector3(mat[1][0], mat[1][1], mat[1][2]).Magnitude();
		retVal.z = Vector3(mat[2][0], mat[2][1], mat[2][2]).Magnitude();
		return retVal;
	}

	static Matrix4 CreateScale(float xScale, float yScale, float zScale)
	{
		float temp[4][4] =
		{
			{ xScale, 0.0f, 0.0f, 0.0f },
			{ 0.0f, yScale, 0.0f, 0.0f },
			{ 0.0f, 0.0f, zScale, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateScale(const Vector3& scaleVector)
	{
		return CreateScale(scaleVector.x, scaleVector.y, scaleVector.z);
	}

	static Matrix4 CreateScale(float scale)
	{
		return CreateScale(scale, scale, scale);
	}

	static Matrix4 CreateRotationX(float theta)
	{
		float temp[4][4] =
		{
			{ 1.0f, 0.0f, 0.0f , 0.0f },
			{ 0.0f, Maths::Cos(theta), -Maths::Sin(theta), 0.0f },
			{ 0.0f, Maths::Sin(theta), Maths::Cos(theta), 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateRotationY(float theta)
	{
		float temp[4][4] =
		{
			{ Maths::Cos(theta), 0.0f, Maths::Sin(theta), 0.0f },
			{ 0.0f, 1.0f, 0.0f, 0.0f },
			{ -Maths::Sin(theta), 0.0f, Maths::Cos(theta), 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateRotationZ(float theta)
	{
		float temp[4][4] =
		{
			{ Maths::Cos(theta), -Maths::Sin(theta), 0.0f, 0.0f },
			{ Maths::Sin(theta), Maths::Cos(theta), 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateTranslation(const Vector3& trans)
	{
		float temp[4][4] =
		{
			{ 1.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ trans.x, trans.y, trans.z, 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateSimpleViewProj(float width, float height)
	{
		float temp[4][4] =
		{
			{ 2.0f / width, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 2.0f / height, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateFromQuaternion(const Quaternion& q)
	{
		float mat[4][4];

		mat[0][0] = 1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z;
		mat[0][1] = 2.0f * q.x * q.y + 2.0f * q.w * q.z;
		mat[0][2] = 2.0f * q.x * q.z - 2.0f * q.w * q.y;
		mat[0][3] = 0.0f;

		mat[1][0] = 2.0f * q.x * q.y - 2.0f * q.w * q.z;
		mat[1][1] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z;
		mat[1][2] = 2.0f * q.y * q.z + 2.0f * q.w * q.x;
		mat[1][3] = 0.0f;

		mat[2][0] = 2.0f * q.x * q.z + 2.0f * q.w * q.y;
		mat[2][1] = 2.0f * q.y * q.z - 2.0f * q.w * q.x;
		mat[2][2] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y;
		mat[2][3] = 0.0f;

		mat[3][0] = 0.0f;
		mat[3][1] = 0.0f;
		mat[3][2] = 0.0f;
		mat[3][3] = 1.0f;

		return Matrix4(mat);
	}

	static Matrix4 CreateLookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
	{
		Vector3 zaxis = Vector3::Normalize(target - eye);
		Vector3 xaxis = Vector3::Normalize(Vector3::Cross(up, zaxis));
		Vector3 yaxis = Vector3::Normalize(Vector3::Cross(zaxis, xaxis));
		Vector3 trans;
		trans.x = -Vector3::Dot(xaxis, eye);
		trans.y = -Vector3::Dot(yaxis, eye);
		trans.z = -Vector3::Dot(zaxis, eye);

		float temp[4][4] =
		{
			{ xaxis.x, yaxis.x, zaxis.x, 0.0f },
			{ xaxis.y, yaxis.y, zaxis.y, 0.0f },
			{ xaxis.z, yaxis.z, zaxis.z, 0.0f },
			{ trans.x, trans.y, trans.z, 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateOrtho(float width, float height, float near, float far)
	{
		float temp[4][4] =
		{
			{ 1.0f / width, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f / height, 0.0f, 0.0f },
			{ 0.0f, 0.0f, -2.0f / (far - near), 0.0f },
			{ 0.0f, 0.0f, (far + near) / (near - far), 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 CreatePerspectiveFOV(float fovY, float width, float height, float near, float far)
	{
		float yScale = Maths::Cot(fovY / 2.0f);
		float xScale = yScale * height / width;
		float temp[4][4] =
		{
			{ xScale, 0.0f, 0.0f, 0.0f },
			{ 0.0f, yScale, 0.0f, 0.0f },
			{ 0.0f, 0.0f, far / (far - near), 1.0f },
			{ 0.0f, 0.0f, -near * far / (far - near), 0.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 CreatePerspective(float left, float right, float bottom, float top, float near, float far)
	{
		float temp[4][4] =
		{
			{ 2 * near / (right - left), 0.0f, 0.0f, 0.0f },
			{ 0.0f, 2 * near / (top - bottom), 0.0f, 0.0f },
			{ (right + left) / (right - left), (top + bottom) / (top - bottom), (far + near) / (near - far), -1.0f },
			{ 0.0f, 0.0f, 2 * near * far / (near - far), 0.0f }
		};
		return Matrix4(temp);
	}

	static const Matrix4 Identity;
};