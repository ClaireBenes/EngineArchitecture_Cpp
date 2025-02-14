#include "AssetManager.h"

#include "Engine/Log.h"

#include <filesystem>
#include <sstream>


std::map<std::string, Texture> AssetManager::mTextures = {};

Texture AssetManager::LoadTexture(Renderer& pRenderer, const std::string& pFileName, const std::string& pName)
{
	printf("fileName : %s, Name : %s\n", pFileName.c_str(), pName.c_str());

	mTextures[pName] = LoadTextureFromFile(pRenderer, pFileName);
	return mTextures[pName];

}

void AssetManager::LoadTexturesFromFolder(Renderer& pRenderer, const std::string& pPathName, std::vector<Texture>& pAllTextures)
{
	std::filesystem::directory_iterator it(pPathName);

	for(const auto& entry : it)
	{
		auto& filePath = entry.path();
		if(entry.is_directory())
		{
			continue;
		}

		//load texture from filepath, creating name for it taking the texture name, adding it to vector
		pAllTextures.push_back(LoadTexture(pRenderer, filePath.string(), filePath.filename().replace_extension().string()));
	}
}

Texture& AssetManager::GetTexture(const std::string& pName)
{
	if (mTextures.find(pName) == mTextures.end())
	{
		std::ostringstream loadError;
		loadError << "Texture " << pName << " does not exist in assets manager\n";
		Log::Error(LogType::Application, loadError.str());
	}
	return mTextures[pName];
}

void AssetManager::Clear()
{
	for (auto texture : mTextures)
	{
		texture.second.Unload();
	}
	mTextures.clear();
}

Texture AssetManager::LoadTextureFromFile(Renderer& pRenderer, const std::string& pFileName)
{
	Texture texture;
	texture.Load(pRenderer, pFileName);
	return texture;
}
