#pragma once

#include "Engine/GameTool/Utility/Vector/Vector3.h"
#include "Engine/GameTool/Utility/Quaternion/Quaternion.h"

#include <memory.h>

/**
 * @brief Matrix4 represents a 4x4 matrix used for transformations in 3D space.
 * It supports various operations such as matrix multiplication, inversion, and extracting different transformation components (e.g., translation, rotation, scale).
 * This matrix can also be constructed for specific transformations like scaling, rotating, and translating, as well as for creating projection matrices for rendering.
 */
class Matrix4
{
public:
	float mat[4][4]; // 4x4 matrix to store the transformation values

	/**
	 * @brief Default constructor for Matrix4.
	 * Initializes the matrix as an identity matrix by default.
	 */
	Matrix4();
	/**
	 * @brief Constructor that initializes the matrix with a 4x4 float array.
	 * @param inMat A 4x4 matrix to initialize the object with.
	 */
	explicit Matrix4(float inMat[4][4]);

	/**
	 * @brief Returns the matrix as a const float pointer for direct access to the raw data.
	 * @return A pointer to the raw float data of the matrix.
	 */
	const float* GetAsFloatPtr() const;

	/**
	 * @brief Multiplies two matrices and returns the resulting matrix.
	 * @param a The first matrix.
	 * @param b The second matrix.
	 * @return The result of multiplying matrix a with matrix b.
	 */
	friend Matrix4 operator*(const Matrix4& a, const Matrix4& b);

	/**
	 * @brief Multiplies the current matrix by another matrix (a * b).
	 * @param right The matrix to multiply the current matrix by.
	 * @return The updated matrix.
	 */
	Matrix4& operator*=(const Matrix4& right);

	/**
	 * @brief Inverts the matrix (calculates its inverse).
	 * This operation is computationally expensive and should be used carefully.
	 */
	void Invert();

	/**
	 * @brief Extracts the translation vector from the matrix (the position).
	 * @return A Vector3 representing the translation part of the matrix.
	 */
	Vector3 GetTranslation() const;

	/**
	 * @brief Extracts the X-axis direction vector from the matrix (usually for orientation).
	 * @return A normalized Vector3 representing the X-axis.
	 */
	Vector3 GetXAxis() const;
	/**
	 * @brief Extracts the Y-axis direction vector from the matrix (usually for orientation).
	 * @return A normalized Vector3 representing the Y-axis.
	 */
	Vector3 GetYAxis() const;
	/**
	 * @brief Extracts the Z-axis direction vector from the matrix (usually for orientation).
	 * @return A normalized Vector3 representing the Z-axis.
	 */
	Vector3 GetZAxis() const;

	/**
	 * @brief Extracts the scaling factors from the matrix (how much the object is scaled along each axis).
	 * @return A Vector3 representing the scale along each axis.
	 */
	Vector3 GetScale() const;

	/**
	 * @brief Creates a scaling matrix using individual scale factors for each axis.
	 * @param xScale The scale factor along the X-axis.
	 * @param yScale The scale factor along the Y-axis.
	 * @param zScale The scale factor along the Z-axis.
	 * @return A new Matrix4 representing the scaling transformation.
	 */
	static Matrix4 CreateScale(float xScale, float yScale, float zScale);
	/**
	 * @brief Creates a scaling matrix using a Vector3 to specify the scale for each axis.
	 * @param scaleVector The scaling vector containing the scale for X, Y, and Z axes.
	 * @return A new Matrix4 representing the scaling transformation.
	 */
	static Matrix4 CreateScale(const Vector3& scaleVector);
	/**
	 * @brief Creates a uniform scaling matrix where all axes are scaled by the same factor.
	 * @param scale The uniform scaling factor.
	 * @return A new Matrix4 representing the uniform scaling transformation.
	 */
	static Matrix4 CreateScale(float scale);

	/**
	 * @brief Creates a rotation matrix for rotation around the X-axis.
	 * @param theta The angle (in radians) to rotate around the X-axis.
	 * @return A new Matrix4 representing the rotation transformation.
	 */
	static Matrix4 CreateRotationX(float theta);
	/**
	 * @brief Creates a rotation matrix for rotation around the Y-axis.
	 * @param theta The angle (in radians) to rotate around the Y-axis.
	 * @return A new Matrix4 representing the rotation transformation.
	 */
	static Matrix4 CreateRotationY(float theta);
	/**
	 * @brief Creates a rotation matrix for rotation around the Z-axis.
	 * @param theta The angle (in radians) to rotate around the Z-axis.
	 * @return A new Matrix4 representing the rotation transformation.
	 */
	static Matrix4 CreateRotationZ(float theta);


	/**
	 * @brief Creates a translation matrix that moves an object by a given translation vector.
	 * @param trans The translation vector to apply to the object.
	 * @return A new Matrix4 representing the translation transformation.
	 */
	static Matrix4 CreateTranslation(const Vector3& trans);

	/**
	 * @brief Creates a simple orthogonal view projection matrix.
	 * Typically used for 2D rendering or simple orthographic projections.
	 * @param width The width of the viewport or projection.
	 * @param height The height of the viewport or projection.
	 * @return A new Matrix4 representing a simple orthogonal projection.
	 */
	static Matrix4 CreateSimpleViewProj(float width, float height);

	/**
	 * @brief Creates a rotation matrix from a quaternion representation.
	 * @param q The quaternion to convert to a matrix.
	 * @return A new Matrix4 representing the rotation described by the quaternion.
	 */
	static Matrix4 CreateFromQuaternion(const Quaternion& q);

	/**
	 * @brief Creates a "look-at" matrix for setting up camera orientation.
	 * @param eye The position of the camera.
	 * @param target The point the camera is looking at.
	 * @param up The "up" vector that defines the orientation of the camera.
	 * @return A new Matrix4 representing the view transformation for the camera.
	 */
	static Matrix4 CreateLookAt(const Vector3& eye, const Vector3& target, const Vector3& up);

	/**
	 * @brief Creates an orthographic projection matrix (used for 2D rendering).
	 * @param width The width of the view frustum.
	 * @param height The height of the view frustum.
	 * @param near The near clipping plane.
	 * @param far The far clipping plane.
	 * @return A new Matrix4 representing the orthographic projection transformation.
	 */
	static Matrix4 CreateOrtho(float width, float height, float near, float far);

	/**
	 * @brief Creates a perspective projection matrix with a specified field of view.
	 * @param fovY The vertical field of view (in radians).
	 * @param width The width of the viewport.
	 * @param height The height of the viewport.
	 * @param near The near clipping plane.
	 * @param far The far clipping plane.
	 * @return A new Matrix4 representing the perspective projection transformation.
	 */
	static Matrix4 CreatePerspectiveFOV(float fovY, float width, float height, float near, float far);

	/**
	 * @brief Creates a perspective projection matrix with specified frustum values.
	 * @param left The left boundary of the near plane.
	 * @param right The right boundary of the near plane.
	 * @param bottom The bottom boundary of the near plane.
	 * @param top The top boundary of the near plane.
	 * @param near The near clipping plane.
	 * @param far The far clipping plane.
	 * @return A new Matrix4 representing the perspective projection transformation.
	 */
	static Matrix4 CreatePerspective(float left, float right, float bottom, float top, float near, float far);

	/**
	 * @brief Constant for the identity matrix (no transformation)
	 */ 
	static const Matrix4 Identity;
};