#pragma once

/*
VertexArray is a class that encapsulates an OpenGL Vertex Array Object (VAO) and its associated buffers. 
It handles the creation and management of vertex buffers and index buffers, 
along with setting up the appropriate vertex attributes for rendering. 
This class is used to store and manage vertex data in memory for rendering purposes in OpenGL.
*/
class VertexArray
{
public:
	/*
	Constructor for VertexArray.
	Initializes and creates a vertex array object (VAO) and its associated buffers
	using the provided vertex data.
	@param pVertices A pointer to an array of vertex data.
	@param pVerticeCount The number of vertices in the array.
	*/
	VertexArray(const float* pVertices, unsigned int pVerticeCount);
	/*
	Destructor for VertexArray.
	Cleans up and deletes the VAO and buffers from OpenGL memory.
	*/
	~VertexArray();

	/*
	Binds the vertex array to be the current active vertex array in OpenGL.
	*/
	void SetActive();

	/*
	Gets the count of vertices in the vertex array.
	@return The number of vertices stored in the vertex array.
	*/
	unsigned int GetVerticeCount() const;

private:
	unsigned int mVerticeCount; // The number of vertices.
	unsigned int mVertexArrayId; // The OpenGL ID for the vertex array object (VAO).
	unsigned int mVertexBufferId; // The OpenGL ID for the vertex buffer object (VBO).
	unsigned int mIndexBufferId; // The OpenGL ID for the index buffer object (IBO).
};


