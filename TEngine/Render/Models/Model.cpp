#include "Model.h"

#include "Mesh.h"
#include "Vertex.h"

#include "../../Core/PortableTypes.h"
#include "../../Core/Math/Vector3.h"
#include "../../Core/Math/Vector2.h"
#include "../Shader/Shader.h"
#include "../Texture/Texture.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stdexcept>
#include <iostream>

namespace TEngine
{
	void Model::Draw(Shader shader)
	{
		/*for (maxint i = 0; i < meshes.size(); i++)
			meshes[i].Draw(shader);*/
	}

	Mesh Model::GetMeshCopy(maxint index)
	{
		return meshes[index];
	}

	maxint Model::GetMeshCount()
	{
		return meshes.size();
	}

	void Model::LoadModel(std::string path)
	{
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			throw std::exception(import.GetErrorString());
		}

		directory = path.substr(0, path.find_last_of('\\'));

		ProcessNode(scene->mRootNode, scene);
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		// process all the node's meshes (if any)
		for (maxint i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(ProcessMesh(mesh, scene));
		}
		// then do the same for each of its children
		for (maxint i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<uint32> indices;
		std::vector<Texture> textures;

		for (maxint i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			
			// Process vertex position
			Vector3 vector;
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.position = vector;

			// Process vertex normal
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;

			// Process the texture co-ordinates
			if (mesh->mTextureCoords[0]) 
			{
				Vector2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.textCoords = vec;
			}
			else 
			{
				vertex.textCoords = Vector2(0.0f, 0.0f);
			}

			vertices.push_back(vertex);
		}

		// Process indices
		for (maxint i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (maxint j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
		
		// Process material
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			std::vector<Texture> diffuseMaps = LoadMaterialTextures(material,
				aiTextureType_DIFFUSE, TexType::diffuse);
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

			std::vector<Texture> specularMaps = LoadMaterialTextures(material,
				aiTextureType_SPECULAR, TexType::specular);
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		return Mesh(vertices, indices, textures);
	}

	std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, TexType typeName)
	{
		std::vector<Texture> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			Texture texture(directory + "\\" + str.C_Str(), typeName);
			texture.Load();
			textures.push_back(texture);
		}

		return textures;
	}
}
