#pragma once

#include "Engine/GameTool/Visual/Texture.h"
#include "Engine/GameTool/Visual/Mesh/Mesh.h"

#include <map>
#include <string>
#include <vector>

#define TINYOBJLOADER_IMPLEMENTATION

class IRenderer;

class AssetManager
{
public:
	AssetManager(const AssetManager&) = delete;
	AssetManager& operator=(const AssetManager&) = delete;

	static Texture* LoadTexture(IRenderer& pRenderer, const std::string& pFileName, const std::string& pName);
	static void LoadTexturesFromFolder(IRenderer& pRenderer, const std::string& pPathName, std::vector<Texture*>& pAllTextures);
	static Texture* GetTexture(const std::string& pName);

	static Mesh* LoadMesh(const std::string& pFileName, const std::string& pName);
	static Mesh* GetMesh(const std::string& pName);

	static void Clear();

private:
	AssetManager() = default;

	//Storage for future References
	static std::map<std::string, Texture*> mTextures;
	static std::map<std::string, Mesh*> mMeshes;

	static Texture* LoadTextureFromFile(IRenderer& pRenderer, const std::string& pFileName);
	static Mesh* LoadMeshFromFile(const std::string& pFileName);
};

