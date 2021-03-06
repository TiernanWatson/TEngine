#include "ModelImporter.h"
#include "TextureImporter.h"
#include "ResourceLoader.h"
#include "Types/Texture.h"
#include "Types/Material.h"
#include "Types/Mesh.h"
#include "../Render/Vertex.h"
#include "../Helpers/Debug.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace TEngine
{
	ModelImporter::ModelImporter(U32 maxInCache)
		: ResourceImporter(maxInCache)
	{
	}

	Model& ModelImporter::Load(const std::string& path, bool useCache)
	{
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_FlipWindingOrder);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			throw std::exception(import.GetErrorString());
		}

		std::string directory = path.substr(0, path.find_last_of('\\'));

		std::vector<Mesh*> meshes;
		ProcessNode(scene->mRootNode, scene, directory, meshes);

		loaded_resources_[path] = Model(meshes, 0, path);

		return loaded_resources_[path];
	}

	void ModelImporter::ProcessNode(aiNode* node, const aiScene* scene, std::string& directory, std::vector<Mesh*>& meshes)
	{
		// process all the node's meshes_ (if any)
		for (USIZE i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			//loaded_meshes_.push_back(ProcessMesh(mesh, scene, directory));
			meshes.push_back(ProcessMesh(mesh, scene, directory));
		}
		
		// then do the same for each of its children
		for (USIZE i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene, directory, meshes);
		}
		
	}

	Mesh* ModelImporter::ProcessMesh(aiMesh* mesh, const aiScene* scene, std::string& directory)
	{
		std::vector<Vertex> vertices;
		std::vector<U32> indices;
		std::vector<Texture> textures;

		for (USIZE i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;

			// Process vertex position
			Vector3 vector;
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.position = vector;

			// Process vertex normal_
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;

			// Process vertex tangent
			/*vector.x = mesh->mTangents[i].x;
			vector.y = mesh->mTangents[i].y;
			vector.z = mesh->mTangents[i].z;
			vertex.tangent = vector;
			// Process vertex bitangent
			vector.x = mesh->mBitangents[i].x;
			vector.y = mesh->mBitangents[i].y;
			vector.z = mesh->mBitangents[i].z;
			vertex.bitangent = vector;*/

			// Process the dx_texture_ co-ordinates
			if (mesh->mTextureCoords[0])
			{
				Vector2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.tex_coord = vec;
			}
			else
			{
				vertex.tex_coord = Vector2(0.0f, 0.0f);
			}

			vertices.push_back(vertex);
		}

		// Process indices_
		for (USIZE i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (USIZE j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		// Process material
		std::vector<Texture*> diffuse_maps, specular_maps;
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		LoadMaterialTextures(material, aiTextureType_DIFFUSE, TexType::diffuse, directory, diffuse_maps);
		//textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());

		LoadMaterialTextures(material, aiTextureType_SPECULAR, TexType::specular, directory, specular_maps);
		//textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());

		/*std::vector<Texture> normalMaps = LoadMaterialTextures(material,
			aiTextureType_HEIGHT, TexType::normal_);
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		std::vector<Texture> heightMaps = LoadMaterialTextures(material,
			aiTextureType_AMBIENT, TexType::height_);
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());*/

		assert(vertices.size() != 0 && indices.size() != 0);

		// TODO: Proper material management
		Material* mat = new Material(diffuse_maps.size() != 0 ? diffuse_maps[0] : nullptr, 
			specular_maps.size() != 0 ? specular_maps[0] : nullptr, 
			nullptr, nullptr, 0, "");

		return new Mesh(vertices, indices, { mat }, 0, "");
	}

	void ModelImporter::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, TexType typeName, std::string& directory, std::vector<Texture*>& result)
	{
		for (U32 i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			Texture& texture = ResourceLoader::Instance().GetTexture(directory + "\\" + str.C_Str());
			texture.SetType(typeName);
			result.push_back(&texture);
		}
	}
}
