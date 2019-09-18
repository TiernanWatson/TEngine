#include "Shader.h"
#include <glad/glad.h>
#include <glfw3.h>
#include <stdexcept>
#include "../../Core/Math/Vector4.h"
#include "../../Core/Math/Matrix4.h"

namespace TEngine
{
	Shader::Shader()
	{
	}

	Shader::Shader(const char* vertexSource, const char* fragSource)
	{
		uint32 vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
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

		shaderProgram = glCreateProgram();
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
	}

	void Shader::Use()
	{
		glUseProgram(shaderProgram);
	}

	void Shader::SetVec4(const std::string& name, const Vector4& value)
	{
		glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()),
			value.x, value.y, value.z, value.w);
	}

	void Shader::SetMat4(const std::string& name, const Matrix4& value)
	{
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 
			1, GL_FALSE, value.flat);
	}
}
