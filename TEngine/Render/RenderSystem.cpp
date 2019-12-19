#include "RenderSystem.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "../Core/IO/FileSystem.h"
#include "../Core/Math/Vector4.h"
#include "../Core/Math/Matrix4.h"
#include "../Core/Math/TMath.h"
#include "../ECS/EntityManager.h"
#include "../ECS/ComponentManager.h"
#include "../ECS/Components/Transform.h"
#include "../ECS/Components/MeshComponent.h"
#include <iostream>

namespace TEngine
{
	void RenderSystem::SetupVertexData()
	{
		glEnable(GL_DEPTH_TEST);

		model = Model("D:\\3D Models\\nanosuit\\nanosuit.obj");
	}

	void RenderSystem::SetupMesh(const Mesh& mesh, uint32& VAO, uint32& VBO, uint32& EBO)
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		// Gather all vertices
		glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), &mesh.vertices[0], GL_STATIC_DRAW);

		// Index the vertices for drawing
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), &mesh.indices[0], GL_STATIC_DRAW);

		// Vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// Vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		// Vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textCoords));

		glBindVertexArray(0);
	}

	RenderSystem::RenderSystem()
	{
		
	}

	void RenderSystem::StartUp(GLFWwindow* window)
	{
		this->window = window;

		const char* vertSource = FileSystem::Instance().ReadString(
			"D:\\TEngine\\TEngine\\Shaders\\Vertex\\default.vert");

		const char* fragSource = FileSystem::Instance().ReadString(
			"D:\\TEngine\\TEngine\\Shaders\\Fragment\\default.frag");

		shader = Shader(vertSource, fragSource);

		delete vertSource, fragSource;

		SetupVertexData();

		for (size i = 0; i < model.GetMeshCount(); i++)
		{
			uint32 ent = EntityManager::Main().NewEntity();
			std::cout << "Created entity: " << ent << std::endl;

			Transform t = ComponentManager<Transform>::Main().AddToEntity(ent);
			std::cout << "Added transform" << std::endl;

			t.localPosition = Vector3::down * 1.75f;
			t.localRotation = Vector3::zero;
			t.localScale = Vector3::one * 0.2f;

			MeshComponent m = ComponentManager<MeshComponent>::Main().AddToEntity(ent);
			std::cout << "Added Mesh" << std::endl;

			Mesh mesh = model.GetMeshCopy(i);

			SetupMesh(mesh, m.VAO, m.VBO, m.EBO);

			std::cout << "ABE: " << m.VAO << " " << m.VBO << " " << m.EBO << std::endl;

			
		}
	}

	void RenderSystem::Update(float32 deltaTime)
	{
		glClearColor(.3f, .2f, .2f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Matrix4 worldToCamera = Matrix4::ModelToWorld(Vector3::forward * -5.f, Vector3::one, Vector3(0.f, TMath::PI, 0.f)).Inverse();
		Matrix4 cameraToClip = Matrix4::Projection(TMath::PI_4, 16.f / 9.f, 100.f, 0.1f);

		Vector3 translate = Vector3::down * 1.75f;
		Vector3 rotate = Vector3::zero;
		Vector3 scale = Vector3::one * 0.2f;
		Matrix4 modelToWorld = Matrix4::ModelToWorld(translate, scale, rotate);

		shader.Use();
		shader.SetMat4("view", worldToCamera.Transpose());
		shader.SetMat4("projection", cameraToClip.Transpose());
		shader.SetMat4("model", modelToWorld.Transpose());

		uint32 entities[MAX_ENTITIES];
		EntityManager::Main().GetEntitiesByMask(1, entities);

		//model.Draw(shader);

		// Loop all entities with meshes and render them
		for (const uint32& e : entities)
		{
			if (e == -1)
				break; 

			std::cout << "Update ent " << e << std::endl;
			Transform t = ComponentManager<Transform>::Main().GetByEntity(e);
			MeshComponent m = ComponentManager<MeshComponent>::Main().GetByEntity(e);

			//Matrix4 modelToWorld = Matrix4::ModelToWorld(t.localPosition, t.localScale, t.localRotation);
			//shader.SetMat4("model", modelToWorld.Transpose());

			// Activate texture
			//glActiveTexture(GL_TEXTURE0);
			//glBindTexture(GL_TEXTURE_2D, m.texture);

			// Do drawing
			glBindVertexArray(m.VAO);
			glDrawElements(GL_TRIANGLES, m.indexCount, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			//model.Draw(shader);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}

	void RenderSystem::ShutDown()
	{
		this->window = nullptr;
	}
}
