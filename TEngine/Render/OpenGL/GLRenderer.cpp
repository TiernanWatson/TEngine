#ifdef OPENGL

#include "GLRenderer.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "../../World/WorldSystem.h"
#include "../../World/World.h"
#include "../../Core/IO/FileSystem.h"
#include "../../Core/Math/Vector4.h"
#include "../../Core/Math/Matrix4.h"
#include "../../Core/Math/TMath.h"
#include "../../ECS/EntityManager.h"
#include "../../ECS/Components/Transform.h"
#include "../../ECS/Components/MeshComponent.h"
#include "../../ECS/Components/Camera.h"
#include "../../ECS/Components/PointLight.h"
#include "../../Resources/Types/Texture.h"
#include "../../Resources/Types/Material.h"
#include "../../Resources/Types/Mesh.h"
#include "../../Helpers/Debug.h"
#include "../UI/Font.h"
#include "../Material/Shaders.h"
#include "../Vertex.h"

namespace TEngine
{
	GLRenderer::GLRenderer() : 
		window(nullptr), 
		worlds(nullptr), 
		world(nullptr)
	{
	}

	void GLRenderer::StartUp(GLFWwindow* window, WorldSystem* worlds)
	{
		this->window = window;
		this->worlds = worlds;
		this->world = worlds->GetCurrentWorld();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);

		// Create mesh instances and load each mesh onto GPU
		EntityManager& e = world->GetEntities();
		e.ForEach<Transform, MeshComponent>(
			[this](Transform* t, MeshComponent* m)
			{
				m->indexCount = (GLsizei)m->mesh->GetIndices().size();

				if (meshInstances.count(m->mesh) != 0)
				{
					GLMeshInstance* instance = meshInstances[m->mesh];
					m->VAO = instance->GetVAO();
					m->textures = (GLTextureInfo*)instance->GetTextures();
					m->texCount = instance->GetTextureCount();
				}
				else  // generate mesh instance_ if none exists
				{
					GLMeshInstance* newInstance = new GLMeshInstance(m->mesh);
					newInstance->Load();

					m->VAO = newInstance->GetVAO();
					m->textures = (GLTextureInfo*)newInstance->GetTextures();
					m->texCount = newInstance->GetTextureCount();

					meshInstances[m->mesh] = newInstance;
				}
			}
		);

		shader = Shaders::GetDefault();
	}

	void GLRenderer::Render(float32 deltaTime)
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Get camera details and set kUp the constant matrices
		Transform& camT = world->GetEntities().GetComponent<Transform>(world->GetMainCameraEnt());
		Camera& camC = world->GetEntities().GetComponent<Camera>(world->GetMainCameraEnt());

		Matrix4 view = Matrix4::ModelToWorld(camT.position, camT.scale, camT.rotation).Inverse();
		Matrix4 projection = Matrix4::Projection(camC.FOV, camC.aspect, camC.farDist, camC.nearDist);

		glUseProgram(shader);

		// Send matrices to GPU
		Shaders::SetMat4(shader, "view", view.Transpose());
		Shaders::SetMat4(shader, "projection", projection.Transpose());
		Shaders::SetVec3(shader, "eyePos", camT.position);

		// Now render each mesh
		EntityManager& e = world->GetEntities();
		e.ForEach<Transform, MeshComponent>(
			[this](Transform* t, MeshComponent* m)
			{
				Matrix4 model = Matrix4::ModelToWorld(t->position, t->scale, t->rotation);

				Shaders::SetMat4(shader, "model", model.Transpose());

				// Texture handling
				uint32 diffuseNum = 0;
				uint32 specularNum = 0;
				uint32 normalNum = 0;
				uint32 heightNum = 0;

				for (uint32 i = 0; i < m->texCount; i++)
				{
					glActiveTexture(GL_TEXTURE0 + (GLenum)i);

					std::string uniformName;
					switch (m->GetTexInfo(i).type)
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
						throw std::exception("GLRenderer::Render: TexType invalid");
					}

					glUniform1i(glGetUniformLocation(shader, uniformName.c_str()), i);
					glBindTexture(GL_TEXTURE_2D, m->GetTexInfo(i).id);
				}

				// Draw the mesh using indices_
				glBindVertexArray(m->VAO);
				glDrawElements(GL_TRIANGLES, m->indexCount, GL_UNSIGNED_INT, 0);
				glBindVertexArray(0);

				glActiveTexture(GL_TEXTURE0);
			}
		);
	}

	void GLRenderer::ShutDown()
	{
		this->window = nullptr;
		this->worlds = nullptr;
		this->world = nullptr;

		for (const std::pair<Mesh*, GLMeshInstance*>& p : meshInstances)
		{
			p.second->Unload();
			delete p.second;
		}
	}
}

#endif
