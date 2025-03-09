#pragma once

class VertexArray
{
public:
	VertexArray(const float* pVertices, unsigned int pVerticeCount, const unsigned int* pIndices, unsigned int pIndexCount);
	~VertexArray();

	//functions
	void SetActive();

	//Getters
	unsigned int GetVerticeCount() const;
	unsigned int GetIndicesCount() const;

private:
	unsigned int mVerticeCount;
	unsigned int mIndexCount;

	unsigned int mVertexArrayId;
	unsigned int mVertexBufferId;
	unsigned int mIndexBufferId;
};


