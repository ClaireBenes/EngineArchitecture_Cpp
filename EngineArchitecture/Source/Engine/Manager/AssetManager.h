#pragma once

#include "Engine/GameTool/Visual/Texture.h"

#include <map>
#include <string>
#include <vector>

class RendererSDL;

class AssetManager
{
public:
	AssetManager(const AssetManager&) = delete;
	AssetManager& operator=(const AssetManager&) = delete;

	static Texture LoadTexture(RendererSDL& pRenderer, const std::string& pFileName, const std::string& pName);
	static void LoadTexturesFromFolder(RendererSDL& pRenderer, const std::string& pPathName, std::vector<Texture>& pAllTextures);
	static Texture& GetTexture(const std::string& pName);
	static void Clear();

	//Storage for future References
	static std::map<std::string, Texture> mTextures;

private:
	AssetManager() = default;

	static Texture LoadTextureFromFile(RendererSDL& pRenderer, const std::string& pFileName);
};

