#include "AssetManager.h"

#include "Engine/Log.h"

#include <sstream>

std::map<std::string, Texture> AssetManager::mTextures = {};

Texture AssetManager::LoadTexture(Renderer& pRenderer, const std::string& pFileName, const std::string& pName)
{
	mTextures[pName] = LoadTextureFromFile(pRenderer, pFileName);
	return mTextures[pName];

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
