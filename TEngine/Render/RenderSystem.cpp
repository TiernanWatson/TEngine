#include "RenderSystem.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "../World/WorldSystem.h"
#include "../World/World.h"
#include "../Core/IO/FileSystem.h"
#include "../Core/Math/Vector4.h"
#include "../Core/Math/Matrix4.h"
#include "../Core/Math/TMath.h"
#include "UI/Font.h"
#include "Material/Material.h"
#include "../ECS/EntityManager.h"
#include "../ECS/Components/Transform.h"
#include "../ECS/Components/MeshComponent.h"
#include "../ECS/Components/Camera.h"
#include "../Helpers/Debug.h"


namespace TEngine
{
	void TestFunction(Transform* t, MeshComponent* m)
	{
		CONSOLE_PRINT("ok?");
	}

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

		//glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

				glBufferData(GL_ARRAY_BUFFER, m->mesh->vertices.size() * sizeof(Vertex), &m->mesh->vertices[0], GL_STATIC_DRAW);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->EBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, m->mesh->indices.size() * sizeof(unsigned int), &m->mesh->indices[0], GL_STATIC_DRAW);

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textCoords));

				glBindVertexArray(0);
			}
		);
	}

	void RenderSystem::Update(float32 deltaTime)
	{
		glClearColor(0.3f, 0.3f, 0.3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Transform& camT = world->GetEntities().GetComponent<Transform>(world->GetMainCameraEnt());
		Camera& camC = world->GetEntities().GetComponent<Camera>(world->GetMainCameraEnt());

		Matrix4 view = Matrix4::ModelToWorld(camT.position, camT.scale, camT.rotation).Inverse();
		Matrix4 projection = Matrix4::Projection(camC.FOV, camC.aspect, camC.farDist, camC.nearDist);
		
		Shader* shader = nullptr;
		world->GetEntities().ForEach<Transform, MeshComponent>(
			[&shader, &view, &projection](Transform* t, MeshComponent* m)
			{
				Shader* s = m->mesh->materials[0]->GetShader();
				if (s != shader)
				{
					shader = s;
					glUseProgram(s->shaderProgram);
					s->SetMat4("view", view.Transpose());
					s->SetMat4("projection", projection.Transpose());
				}

				Matrix4 model = Matrix4::ModelToWorld(t->position, t->scale, t->rotation);
				s->SetMat4("model", model.Transpose());
				
				glActiveTexture(GL_TEXTURE0);

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
