#pragma once
#include "ResourceImporter.h"
#include "Types/Model.h"
#include "Types/Texture.h"
#include "Types/Mesh.h"
#include <vector>

struct aiScene;
struct aiNode;
struct aiMaterial;
struct aiMesh;
enum aiTextureType;

namespace TEngine
{
	class ModelImporter : public ResourceImporter<Model>
	{
	public:
		ModelImporter(uint32 maxInCache);

		Model& Load(const std::string& path, bool useCache = true);

	protected:
		void ProcessNode(aiNode* node, const aiScene* scene, std::string& directory, std::vector<Mesh*>& meshes);
		
		Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene, std::string& directory);

		void LoadMaterialTextures(aiMaterial* mat, aiTextureType type, TexType typeName, std::string& directory, std::vector<Texture*>& result);

		std::vector<Mesh> loadedMeshes;
	};
}
