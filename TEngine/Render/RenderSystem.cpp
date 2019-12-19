#include "RenderSystem.h"
#include <glad/glad.h>
#include <glfw3.h>
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

		EntityManager e;
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

	}

	void RenderSystem::ShutDown()
	{
		this->window = nullptr;
	}
}
