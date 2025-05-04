#pragma once

#include "Engine/GameTool/Visual/Texture.h"
#include "Engine/GameTool/Visual/Mesh/Mesh.h"

#include <map>
#include <string>
#include <vector>

#define TINYOBJLOADER_IMPLEMENTATION

class IRenderer;

/*
 AssetManager is a static utility class responsible for loading,
 caching, and managing textures and meshes across the application.
 */
class AssetManager
{
public:
	AssetManager(const AssetManager&) = delete;
	AssetManager& operator=(const AssetManager&) = delete;

	/*
	 * Loads a texture from file and stores it with a given name.
	 * @param pRenderer The rendering backend.
	 * @param pFileName Path to the texture file.
	 * @param pName Name to associate with the texture.
	 * @return Pointer to the loaded Texture.
	 */
	static Texture* LoadTexture(IRenderer& pRenderer, const std::string& pFileName, const std::string& pName);
	/*
	 * Loads all textures from a given folder path.
	 * @param pRenderer The rendering backend.
	 * @param pPathName Folder path containing texture files.
	 * @param pAllTextures Output vector filled with loaded textures.
	 */
	static void LoadTexturesFromFolder(IRenderer& pRenderer, const std::string& pPathName, std::vector<Texture*>& pAllTextures);

	/*
	 * Retrieves a previously loaded texture by name.
	 * @param pName Name associated with the texture.
	 * @return Pointer to the Texture or nullptr if not found.
	 */
	static Texture* GetTexture(const std::string& pName);

	/*
	 * Loads a 3D mesh from an .obj file and stores it with a given name.
	 * @param pFileName .obj mesh filename (relative to mesh directory).
	 * @param pName Name to associate with the mesh.
	 * @return Pointer to the loaded Mesh.
	 */
	static Mesh* LoadMesh(const std::string& pFileName, const std::string& pName);
	/*
	 * Retrieves a previously loaded mesh by name.
	 * @param pName Name associated with the mesh.
	 * @return Pointer to the Mesh or nullptr if not found.
	 */
	static Mesh* GetMesh(const std::string& pName);

	/*
	 Frees all loaded assets (textures and meshes).
	 */
	static void Clear();

private:
	// Private constructor to prevent instantiation.
	AssetManager() = default;

	static std::map<std::string, Texture*> mTextures; // Internal texture storage (name -> Texture pointer).
	static std::map<std::string, Mesh*> mMeshes; // Internal mesh storage (name -> Mesh pointer).

	/*
	 * Helper function to load a texture from a file.
	 * @param pRenderer The rendering backend.
	 * @param pFileName Path to the texture file.
	 * @return Pointer to the loaded Texture.
	 */
	static Texture* LoadTextureFromFile(IRenderer& pRenderer, const std::string& pFileName);
	/*
	 * Helper function to load a mesh from a .obj file using TinyObjLoader.
	 * @param pFileName Mesh filename.
	 * @return Pointer to the loaded Mesh.
	 */
	static Mesh* LoadMeshFromFile(const std::string& pFileName);
};

