#include "AssetManager.h"

#include "Engine/Log.h"
#include "Engine/GameTool/Visual/Mesh/tiny_obj_loader.h"

#include <filesystem>
#include <sstream>


std::map<std::string, Texture> AssetManager::mTextures = {};
std::map<std::string, Mesh*> AssetManager::mMeshes = {};

Texture AssetManager::LoadTexture(IRenderer& pRenderer, const std::string& pFileName, const std::string& pName)
{
	printf("fileName : %s, Name : %s\n", pFileName.c_str(), pName.c_str());

	mTextures[pName] = LoadTextureFromFile(pRenderer, pFileName);
	return mTextures[pName];

}

void AssetManager::LoadTexturesFromFolder(IRenderer& pRenderer, const std::string& pPathName, std::vector<Texture>& pAllTextures)
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

Mesh* AssetManager::LoadMesh(const std::string& pFileName, const std::string& pName)
{
	mMeshes[pName] = LoadMeshFromFile(pFileName);
	return mMeshes[pName];
}

void AssetManager::Clear()
{
	for (auto texture : mTextures)
	{
		texture.second.Unload();
	}
	mTextures.clear();
}

Texture AssetManager::LoadTextureFromFile(IRenderer& pRenderer, const std::string& pFileName)
{
	Texture texture;
	texture.Load(pRenderer, pFileName);
	return texture;
}

Mesh* AssetManager::LoadMeshFromFile(const std::string& pFileName)
{
	Mesh loaded;
	tinyobj::attrib_t attributes;

	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warning, errors;
	std::string dir = "Resources/Meshes/";

	bool success = tinyobj::LoadObj(&attributes, &shapes, &materials, &warning, &errors, (dir + pFileName).c_str());
	if (!success)
	{
		Log::Error(LogType::Application, "Mesh " + pFileName + " does not exist or is not .obj");
		return nullptr;
	}
	else
	{
		Log::Info("Mesh " + pFileName + " successfully loaded");
	}

	std::vector<Vertex> vertices;

	for (int i = 0; i < shapes.size(); i++)
	{
		tinyobj::shape_t& shape = shapes[i];
		tinyobj::mesh_t& mesh = shape.mesh;

		for (int j = 0; j < mesh.indices.size(); j++)
		{
			tinyobj::index_t i = mesh.indices[j];
			Vector3 position = Vector3 {
				attributes.vertices[i.vertex_index * 3],
				attributes.vertices[i.vertex_index * 3 + 1],
				attributes.vertices[i.vertex_index * 3 + 2]
			};

			Vector3 normal = Vector3 {
				attributes.normals[i.normal_index * 3],
				attributes.normals[i.normal_index * 3 + 1],
				attributes.normals[i.normal_index * 3 + 2]
			};

			Vector2 texCoord = {
				attributes.texcoords[i.texcoord_index * 2],
				attributes.texcoords[i.texcoord_index * 2 + 1],
			};

			Vertex vert = { position, normal, texCoord };
			vertices.push_back(vert);
		}
	}

	return new Mesh(vertices);
}
