#include "Shaders.h"
#include "../../Core/Math/Matrix4.h"
#include "../../Core/Math/Vector4.h"
#include "../../Core/Math/Vector3.h"
#include "../../Core/Math/Vector2.h"
#include <glad/glad.h>
#include <glfw3.h>

namespace TEngine
{
	// Static member so must be defined here
	std::unordered_map<std::string, uint32> Shaders::nameToShader;

	uint32 Shaders::CreateShader(const std::string& name, const char* vertSource, const char* fragSource)
	{
		uint32 vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertSource, NULL);
		glCompileShader(vertexShader);

		// Check for errors
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			throw std::exception(infoLog);
		}

		uint32 fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fragSource, NULL);
		glCompileShader(fragShader);

		// Check for errors
		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
			throw std::exception(infoLog);
		}

		uint32 shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragShader);
		glLinkProgram(shaderProgram);

		// Check for linking errors
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			throw std::exception(infoLog);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragShader);

		nameToShader[name] = shaderProgram;

		return shaderProgram;
	}

	uint32 Shaders::GetShader(const std::string& name)
	{
		return nameToShader[name];
	}

	void Shaders::SetMat4(uint32 id, const std::string& name, const Matrix4& mat)
	{
		glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()),
			1, GL_FALSE, mat.flat);
	}

	void Shaders::SetVec4(uint32 id, const std::string& name, const Vector4& vec)
	{
		glUniform4f(glGetUniformLocation(id, name.c_str()),
			vec.x, vec.y, vec.z, vec.w);
	}

	void Shaders::SetVec3(uint32 id, const std::string& name, const Vector3& vec)
	{
		glUniform3f(glGetUniformLocation(id, name.c_str()),
			vec.x, vec.y, vec.z);
	}

	void Shaders::SetVec2(uint32 id, const std::string& name, const Vector2& vec)
	{
		glUniform2f(glGetUniformLocation(id, name.c_str()), vec.x, vec.y);
	}

	void Shaders::SetFloat32(uint32 id, const std::string& name, const float32& val)
	{
		glUniform1f(glGetUniformLocation(id, name.c_str()), val);
	}
}