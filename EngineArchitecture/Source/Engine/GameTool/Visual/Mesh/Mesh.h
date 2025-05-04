#pragma once

#include "../Texture.h"
#include "Engine/Shader/ShaderProgram.h"


#include "Engine/Vertex/Vertex.h"

#include <vector>

class VertexArray;
class ShaderProgram;

/*
Mesh represents a drawable collection of vertices, textures, and shader data.
It stores vertex data, manages a vertex array object (VAO), and allows attaching multiple textures.
The mesh also supports serialization of vertex data into a flat array for GPU uploading.
 */
class Mesh
{
public:
	/*
	 Default constructor. Initializes an empty mesh.
	 */
	Mesh();
	/*
	 * Constructs a mesh using a list of vertices.
	 * Automatically creates a vertex array object using the provided vertex data.
	 * @param pVertices The list of vertices that make up the mesh geometry.
	 */
	Mesh(const std::vector<Vertex>& pVertices);

	/*
	 Unloads the mesh by deleting the vertex array object.
	 This frees GPU resources associated with the mesh.
	 */
	void Unload();
	/*
	 * Adds a texture to the mesh. The texture can later be bound during rendering.
	 * @param pTexture Pointer to the texture to add to the mesh.
	 */
	void AddTexture(Texture* pTexture);

	/*
	 * Converts the mesh's vertex data into a flat float array suitable for GPU uploading.
	 * Each vertex contributes 8 floats (position [3], normal [3], uv [2]).
	 * @return Pointer to a newly allocated float array. Caller is responsible for deleting it.
	 */
	float* ToVerticeArray();

	//Getters & Setters

	/*
	 * Retrieves a texture attached to the mesh at a specified index.
	 * @param index The index of the texture in the internal texture list.
	 * @return Pointer to the texture if it exists, otherwise nullptr.
	 */
	Texture* GetTexture(int index);
	/*
	 * Gets the shader program currently assigned to the mesh.
	 * @return The shader program used by this mesh.
	 */
	ShaderProgram GetShaderProgram();
	/*
	 * Gets the vertex array object used to render the mesh.
	 * @return Pointer to the VertexArray object associated with the mesh.
	 */
	VertexArray* GetVertexArray();

	/*
	 * Sets the shader program to be used by the mesh for rendering.
	 * @param pShaderProgram The shader program to assign.
	 */
	void SetShaderProgram(ShaderProgram pShaderProgram);
	/*
	 * Sets the vertex array object (VAO) for the mesh.
	 * This replaces the current VAO if one exists.
	 * @param pVao Pointer to the VertexArray object.
	 */
	void SetVertexArray(VertexArray* pVao);

private:
	std::vector<Texture*> mAllTextures; // List of all textures assigned to the mesh
	VertexArray* mVao = nullptr; // Vertex Array Object representing the mesh geometry

	std::vector<Vertex> mVertices; // List of vertices composing the mesh

	ShaderProgram mMeshShaderProgram; // Shader program used to render the mesh
};

