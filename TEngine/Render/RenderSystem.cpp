#include "RenderSystem.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "../World/WorldSystem.h"
#include "../World/World.h"
#include "../Core/IO/FileSystem.h"
#include "../Core/Math/Vector4.h"
#include "../Core/Math/Matrix4.h"
#include "../Core/Math/TMath.h"
#include "../ECS/EntityManager.h"
#include "../ECS/Components/Transform.h"
#include "../ECS/Components/MeshComponent.h"
#include <iostream>

namespace TEngine
{
	RenderSystem::RenderSystem() : 
		window(nullptr), 
		worlds(nullptr), 
		world(nullptr)
	{
	}

	void RenderSystem::StartUp(GLFWwindow* window, WorldSystem* worlds)
	{
		this->window = window;
		this->worlds = worlds;
		this->world = worlds->GetCurrentWorld();

		const char* vertSource = FileSystem::Instance().ReadString(
			"D:\\TEngine\\TEngine\\Shaders\\Vertex\\default.vert");

		const char* fragSource = FileSystem::Instance().ReadString(
			"D:\\TEngine\\TEngine\\Shaders\\Fragment\\default.frag");

		delete vertSource, fragSource;

		EntityManager& e = world->GetEntities();
		e.ForEach<Transform, MeshComponent>(
			[](Transform* t, MeshComponent* m)
			{
				m->indexCount = m->mesh->indices.size();

				glGenVertexArrays(1, &m->VAO);
				glGenBuffers(1, &m->VBO);
				glGenBuffers(1, &m->EBO);

				glBindVertexArray(m->VAO);
				glBindBuffer(GL_ARRAY_BUFFER, m->VBO);

				// Gather all vertices
				glBufferData(GL_ARRAY_BUFFER, m->mesh->vertices.size() * sizeof(Vertex), &m->mesh->vertices[0], GL_STATIC_DRAW);

				// Index the vertices for drawing
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->EBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, m->mesh->indices.size() * sizeof(unsigned int), &m->mesh->indices[0], GL_STATIC_DRAW);

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
		);
	}

	void RenderSystem::Update(float32 deltaTime)
	{
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Matrix4 worldToCamera = Matrix4::ModelToWorld(Vector3::forward * 5.f, Vector3::one, Vector3(0.f, TMath::PI, 0.f)).Inverse();
		Matrix4 cameraToClip = Matrix4::Projection(TMath::PI_4, 16.f / 9.f, 100.f, 0.1f);

		Vector3 translate = Vector3::down * 0.0f;
		Vector3 rotate = Vector3::zero;
		Vector3 scale = Vector3::one * 1.0f;
		Matrix4 modelToWorld = Matrix4::ModelToWorld(translate, scale, rotate);
		
		world->GetEntities().ForEach<Transform, MeshComponent>(
			[](Transform* t, MeshComponent* m)
			{
				// Activate texture
				//glActiveTexture(GL_TEXTURE0);

				// Do drawing
				glBindVertexArray(m->VAO);
				glDrawElements(GL_TRIANGLES, m->indexCount, GL_UNSIGNED_INT, 0);
				glBindVertexArray(0);
			}
		);
	}

	void RenderSystem::ShutDown()
	{
		this->window = nullptr;
		this->worlds = nullptr;
		this->world = nullptr;
	}
}
