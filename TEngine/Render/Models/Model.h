#pragma once
#include <string>
#include <vector>
#include "Mesh.h"

struct aiScene;
struct aiNode;
struct aiMaterial;
struct aiMesh;
enum aiTextureType;

namespace TEngine
{
	enum class TexType;

	class Model
	{
	public:
		Model() = default;
		Model(const char* path)
		{
			LoadModel(path);
		}

		void Draw(Shader shader);

	private:
		std::vector<Mesh> meshes;
		std::string directory;

		void LoadModel(std::string path);

		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

		std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, TexType typeName);
	};
}
