#include "RenderManager.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "../Core/IO/FileSystem.h"
#include "../Core/Math/Vector4.h"
#include "../Core/Math/Matrix4.h"
#include "../Core/Math/TMath.h"
#include <iostream>

namespace TEngine
{
	void RenderManager::SetupVertexData()
	{
		glEnable(GL_DEPTH_TEST);

		model = Model("D:\\3D Models\\nanosuit\\nanosuit.obj");
	}

	RenderManager::RenderManager()
	{
		
	}

	void RenderManager::StartUp(GLFWwindow* window)
	{
		this->window = window;

		const char* vertSource = FileSystem::Instance().ReadString(
			"D:\\TEngine\\TEngine\\Shaders\\Vertex\\default.vert");

		const char* fragSource = FileSystem::Instance().ReadString(
			"D:\\TEngine\\TEngine\\Shaders\\Fragment\\default.frag");

		shader = Shader(vertSource, fragSource);
		texture = Texture("D:\\TEngine\\TEngine\\Resources\\Textures\\wall.jpg");

		delete vertSource, fragSource;

		SetupVertexData();
	}

	void RenderManager::Update(float32 deltaTime)
	{
		glClearColor(.3f, .2f, .2f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Vector3 translate = Vector3::down * 1.75f;
		Vector3 rotate = Vector3::zero;
		Vector3 scale = Vector3::one * 0.2f;
		Matrix4 modelToWorld = Matrix4::ModelToWorld(translate, scale, rotate);

		Matrix4 worldToCamera = Matrix4::ModelToWorld(Vector3::forward * 3.f, Vector3::one, Vector3::zero).Inverse();

		Matrix4 cameraToClip = Matrix4::Projection(TMath::PI_4, 16.f / 9.f, 100.f, 0.1f);

		texture.Use();

		shader.Use();
		shader.SetMat4("model", modelToWorld.Transpose());
		shader.SetMat4("view", worldToCamera.Transpose());
		shader.SetMat4("projection", cameraToClip.Transpose());

		model.Draw(shader);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	void RenderManager::ShutDown()
	{
		this->window = nullptr;

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
}
