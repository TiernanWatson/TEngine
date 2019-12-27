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
#include "../ECS/Components/PointLight.h"
#include "../Helpers/Debug.h"
#include "Material/Shaders.h"
#include "Texture/Textures.h"

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

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);

		EntityManager& e = world->GetEntities();
		e.ForEach<Transform, MeshComponent>(
			[](Transform* t, MeshComponent* m)
			{
				m->indexCount = m->mesh->indices.size();

				for (Texture& tex : m->mesh->textures)
					Textures::LoadTextureGL(tex);

				// Generate buffers
				glGenVertexArrays(1, &m->VAO);
				glGenBuffers(1, &m->VBO);
				glGenBuffers(1, &m->EBO);

				glBindVertexArray(m->VAO);
				glBindBuffer(GL_ARRAY_BUFFER, m->VBO);
				glBufferData(GL_ARRAY_BUFFER, m->mesh->vertices.size() * sizeof(Vertex), &m->mesh->vertices[0], GL_STATIC_DRAW);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->EBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, m->mesh->indices.size() * sizeof(uint32), &m->mesh->indices[0], GL_STATIC_DRAW);

				// Create attribute pointers
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
				glEnableVertexAttribArray(3);
				glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
				glEnableVertexAttribArray(4);
				glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textCoord));

				glBindVertexArray(0);
			}
		);
	}

	void RenderSystem::Update(float32 deltaTime)
	{
		glClearColor(0.3f, 0.3f, 0.3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Get camera details and set up the constant matrices
		Transform& camT = world->GetEntities().GetComponent<Transform>(world->GetMainCameraEnt());
		Camera& camC = world->GetEntities().GetComponent<Camera>(world->GetMainCameraEnt());

		Matrix4 view = Matrix4::ModelToWorld(camT.position, camT.scale, camT.rotation).Inverse();
		Matrix4 projection = Matrix4::Projection(camC.FOV, camC.aspect, camC.farDist, camC.nearDist);
		
		// Render each compatible entity
		uint32 shader = 0;
		world->GetEntities().ForEach<Transform, MeshComponent>(
			[&camT, &shader, &view, &projection](Transform* t, MeshComponent* m)
			{
				uint32 s = m->mesh->materials[0]->GetShader();
				if (s != shader)
				{
					shader = s;
					glUseProgram(s);
					Shaders::SetMat4(s, "view", view.Transpose());
					Shaders::SetMat4(s, "projection", projection.Transpose());
				}

				Matrix4 model = Matrix4::ModelToWorld(t->position, t->scale, t->rotation);
				Shaders::SetMat4(s, "model", model.Transpose());
				Shaders::SetVec3(s, "eyePos", camT.position);
				
				// Texture handling
				uint32 diffuseNum = 0;
				uint32 specularNum = 0;
				uint32 normalNum = 0;
				uint32 heightNum = 0;

				std::vector<Texture>& textures = m->mesh->textures;
				for (maxint i = 0; i < textures.size(); i++)
				{
					glActiveTexture(GL_TEXTURE0 + i);
					
					std::string uniformName; 
					switch (textures[i].type)
					{
					case TexType::diffuse:
						uniformName = "texDiffuse" + std::to_string(diffuseNum++);
						break;
					case TexType::specular:
						uniformName = "texSpecular" + std::to_string(specularNum++);
						break;
					case TexType::normal:
						uniformName = "texNormal" + std::to_string(normalNum++);
						break;
					case TexType::height:
						uniformName = "texHeight" + std::to_string(heightNum++);
						break;
					default:
						throw std::exception("RenderSystem::Update: TexType invalid");
					}

					glUniform1i(glGetUniformLocation(s, uniformName.c_str()), i);
					glBindTexture(GL_TEXTURE_2D, textures[i].id);
				}

				// Do drawing
				glBindVertexArray(m->VAO);
				glDrawElements(GL_TRIANGLES, m->indexCount, GL_UNSIGNED_INT, 0);
				glBindVertexArray(0);

				glActiveTexture(GL_TEXTURE0);
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
